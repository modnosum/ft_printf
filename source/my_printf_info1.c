/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf_info1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modnosum <modnosum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:57:07 by modnosum          #+#    #+#             */
/*   Updated: 2018/08/20 22:14:36 by modnosum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <my_string.h>

#include <my_printf_info.h>

void			print_result(const char *fmt, const char *p, t_info *info)
{
	update_result(info, p, (fmt - p));
	my_putnstr(info->result, info->cur);
	if (info->result)
		free((void*)info->result);
}

static void		clear_info_helper(t_info *info)
{
	info->is_pointer = 0;
	info->arg_cur = 0;
	info->base = 10;
}

void			clear_info(t_info *info)
{
	if (!info->result)
	{
		info->cur = 0;
		info->size = 200;
		info->result = my_strnew(info->size, 0);
	}
	info->width = 0;
	info->precision = 0;
	info->is_alt = 0;
	info->is_left_adj = 0;
	info->is_plus = 0;
	info->is_space = 0;
	info->is_zero_padd = 0;
	info->is_prec = 0;
	info->size_flag = NO_SIZE;
	info->specifier = 0;
	info->data.p = 0;
	info->arg = 0;
	info->arg_size = 0;
	clear_info_helper(info);
}

void			init_info(t_info *info)
{
	info->result = 0;
	clear_info(info);
}

void			update_result(t_info *info, const char *str, size_t n)
{
	if (n > (info->size - info->cur))
	{
		info->result = my_resize_str(info->result, info->size,
									(info->size * 2) + n);
		info->size = (info->size * 2) + n;
	}
	my_strncpy((info->result + info->cur), str, n);
	info->cur += n;
}
