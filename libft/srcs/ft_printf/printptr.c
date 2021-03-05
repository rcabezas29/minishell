/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 17:16:23 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/05 12:12:15 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putwidth(t_struct *ps, int less, int arglen)
{
	int	i;
	int	widthlen;

	i = 0;
	widthlen = ps->width - arglen;
	if (ps->width != 0 && ((less == 0 && ps->flags[1] == '1')
			|| (less > 0 && ps->flags[1] == '0')))
	{
		while (++i <= widthlen)
			ft_putchar_fd(' ', 1);
		ps->ret += i - 1;
	}
}

static void	ft_putprec(t_struct *ps, int arglen)
{
	int	i;
	int	preclen;

	i = 0;
	preclen = ps->precision;
	if (preclen > arglen)
		ps->precision - arglen;
	if (ps->precision != 0)
	{
		while (++i <= preclen)
			ft_putchar_fd('0', 1);
		ps->ret += i - 1;
	}
}

void	ft_printptr(t_struct *ps, intptr_t arg)
{
	if (ps->width != 0 && arg == 0 && ps->precision == -1)
		ft_putwidth(ps, 1, 2);
	else if (ps->width != 0)
		ft_putwidth(ps, 1, ft_nbrlen_base(arg, "0123456789abcdef") + 2);
	ft_putstr_fd("0x", 1);
	ps->ret += 2;
	if (ps->precision != 0)
		ft_putprec(ps, ft_nbrlen_base(arg, "0123456789abcdef"));
	if (ps->precision != -1)
	{
		ps->ret += ft_nbrlen_base(arg, "0123456789abcdef");
		ft_putnbr_base(arg, "0123456789abcdef");
	}
	if (ps->width != 0 && ps->flags[1] == '1')
		ft_putwidth(ps, 0, ft_nbrlen_base(arg, "0123456789abcdef") + 2);
}
