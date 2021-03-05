/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_s_or_z.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:03:23 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/05 12:05:14 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    put_s_or_z(t_struct *ps)
{
    if (ps->precision == 0 || ps->precision < -1)
	{
		if (ps->flags[0] == '1' && ps->flags[1] == '0')
			ft_putchar_fd(' ', 1);
		else
			ft_putchar_fd('0', 1);
	}
	else
		ft_putchar_fd(' ', 1);
}