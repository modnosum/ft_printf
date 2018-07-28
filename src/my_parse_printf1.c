/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parse_printf1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:47:45 by modnosum          #+#    #+#             */
/*   Updated: 2018/07/28 17:58:14 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <my_string.h>

#include <my_parse_printf.h>

void			my_parse_star(char const **fmt, size_t *number,
				va_list *args)
{
	if (**fmt == '*')
		*number = va_arg(*args, int);
	else
		*number = my_parse_number(fmt);
}

void			my_manage_size_flag(char const **fmt, t_info *info,
				t_size_f new_size)
{
	if (new_size == SHORT_SIZE || new_size == LONG_LONG_SIZE)
		++*fmt;
	if (new_size > info->size)
		info->size = new_size;
}

void			my_parse_size_flags(char const **fmt, t_info *info)
{
	char const	*f;
	char const	*flags;

	flags = "zjhl";
	while ((f = my_strchr(flags, **fmt)))
	{
		if (*f == 'h')
			my_manage_size_flag(fmt, info, (*(f + 1) == 'h' ? SHORT_SIZE
														: CHAR_SIZE));
		else if (*f == 'l')
			my_manage_size_flag(fmt, info, (*(f + 1) == 'l' ? LONG_LONG_SIZE
														: LONG_SIZE));
		else if (*f == 'j')
			my_manage_size_flag(fmt, info, LONG_LONG_SIZE);
		else
			my_manage_size_flag(fmt, info, SIZE_T_SIZE);
		++*fmt;
	}
}

int				my_parse_specifier(char const **fmt, t_info *info)
{
	char		test;

	test = (**fmt >= 'A' && **fmt <= 'Z') ? (**fmt + ('a' - 'A'))
										: (**fmt);
	if (!(test == 's' || test == 'c' || test == 'u' || test == 'o' ||
		test == 'x' || test == 'i' || test == 'd' || test == 'p' ||
		test == '%'))
		return (0);
	if (**fmt == 'S' || **fmt == 'C' || **fmt == 'U' || **fmt == 'O' ||
		**fmt == 'D')
		info->size_flag = LONG_SIZE;
	else if (**fmt == 'X')
		test = 'X';
	if (test == 'i')
		test = 'd';
	info->specifier = test;
	++*fmt;
	return (1);
}

int				my_validate_arg(char const **pos, char const **fmt,
				t_info *info, va_list *args)
{
	int			is_valid;
	char const	*save;

	save = *fmt;
	++*fmt;
	my_parse_flags(fmt, info);
	my_parse_star(fmt, &info->width, args);
	if (**fmt == '.' && ++*fmt)
	{
		info->no_prec = 0;
		my_parse_star(fmt, &info->precision, args);
	}
	my_parse_size_flags(fmt, info);
	if (!(is_valid = my_parse_specifier(fmt, info)))
		*pos = save;
	else
		*pos = *fmt;
	return (is_valid);
}