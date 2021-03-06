/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_form_arg2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 17:01:27 by modnosum          #+#    #+#             */
/*   Updated: 2018/08/12 19:49:39 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_form_arg.h>

static void		manage_string(va_list *args, t_info *info)
{
	if (info->size_flag == LONG_SIZE)
	{
		info->data.ws = va_arg(*args, const wchar_t*);
		if (info->data.ws == 0)
			info->data.ws = L"(null)";
		form_wide_string(info);
	}
	else
	{
		info->data.s = va_arg(*args, const char*);
		if (info->data.s == 0)
			info->data.s = "(null)";
		form_string(info);
	}
}

static void		manage_char(va_list *args, t_info *info)
{
	if (info->size_flag == LONG_SIZE)
	{
		info->data.wc = va_arg(*args, wchar_t);
		form_wide_char(info);
	}
	else
	{
		info->data.c = va_arg(*args, int);
		form_char(info);
	}
}

void			manage_letters(va_list *args, t_info *info)
{
	if (info->specifier == 's')
		manage_string(args, info);
	else
		manage_char(args, info);
}
