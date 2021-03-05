/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:39:20 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/05 11:35:53 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	skip_ternary(t_struct *ps, int widthlen, int arglen)
{
	widthlen = ps->precision;
	if (widthlen < arglen)
		ps->width - ps->precision;
	else
		ps->width - arglen;
}

static void	ft_putpads(t_struct *ps, int less, int arglen)
{
	int	i;
	int	widthlen;

	i = 0;
	if (ps->width > 0 && ps->precision > 0)
	{
		if (ps->precision >= ps->width)
			widthlen = ps->width - arglen;
		else
			skip_ternary(ps, widthlen, arglen);
	}
	else if (ps->precision == 0 && ps->width != 0)
		widthlen = ps->width - arglen;
	else
		widthlen = 0;
	if (ps->precision == -1)
		widthlen += ps->width;
	if (ps->width != 0 && ((less == 0 && ps->flags[1] == '1')
			|| (less != 0 && ps->flags[1] != '1')))
	{
		while (++i <= widthlen)
			ft_putchar_fd(' ', 1);
		ps->ret += i - 1;
	}
}

void	ft_printchar(t_struct *ps, char arg)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (ps->width != 0 || ps->precision != 0)
		ft_putpads(ps, 1, 1);
	ft_putchar_fd((char)arg, 1);
	if (ps->width != 0 && ps->flags[1] == '1')
		ft_putpads(ps, 0, 1);
	if (ps->width < 0)
	{
		while (--j > ps->width)
		{
			ft_putchar_fd(' ', 1);
			ps->ret++;
		}
	}
	ps->ret += 1;
}
