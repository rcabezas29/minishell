/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printuns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 18:05:30 by rcabezas          #+#    #+#             */
/*   Updated: 2020/09/09 09:27:57 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putwidth(t_struct *ps, int less, int arglen)
{
	int	i;
	int	widthlen;
	int	preclen;

	i = 0;
	widthlen = (ps->width - (ps->precision == -1 && arglen == 1 ? 0 : arglen));
	preclen = ps->precision >= arglen ? ps->precision - arglen : 0;
	if (ps->width != 0 && ((less == 0 && ps->flags[1] == '1') ||
				(less != 0 && ps->flags[1] == '0')))
	{
		while (++i <= widthlen - preclen)
		{
			if (ps->precision == 0)
				ft_putchar_fd(ps->flags[0] == '1' && ps->flags[1] == '0' ?
							'0' : ' ', 1);
			else
				ft_putchar_fd(' ', 1);
		}
		ps->ret += i - 1;
	}
}

static void	ft_putprec(t_struct *ps, int arglen)
{
	int	i;
	int	preclen;

	i = 0;
	preclen = ps->precision > arglen ? ps->precision - arglen : 0;
	if (ps->precision != 0)
	{
		while (++i <= preclen)
			ft_putchar_fd('0', 1);
		ps->ret += i - 1;
	}
}

static void	ft_printhex(t_struct *ps, unsigned long long arg)
{
	if (ps->width != 0)
		ft_putwidth(ps, 1, ft_nbrlen_base(arg, "0123456789abcdef"));
	if (ps->precision != 0)
		ft_putprec(ps, ft_nbrlen_base(arg, "0123456789abcdef"));
	if (ps->precision != -1)
		ps->ret += ft_nbrlen_base(arg, "0123456789abcdef");
	if (ps->conversion == 'x' && ps->precision != -1)
		ft_putnbr_base(arg, "0123456789abcdef");
	else if (ps->conversion == 'X' && ps->precision != -1)
		ft_putnbr_base(arg, "0123456789ABCDEF");
	if (ps->precision == -1 && (ps->conversion == 'x' ||
				ps->conversion == 'X') && arg != 0)
	{
		if (ft_isupper(ps->conversion))
			ft_putnbr_base(arg, "0123456789ABCDEF");
		else
			ft_putnbr_base(arg, "0123456789abcdef");
		ps->ret += ft_nbrlen_base(arg, "0123456789abcdef");
	}
	if (ps->flags[1] == '1')
		ft_putwidth(ps, 0, ft_nbrlen_base(arg, "0123456789abcdef"));
}

void		ft_printuns(t_struct *ps, unsigned long long arg)
{
	if (ps->conversion == 'x' || ps->conversion == 'X')
		ft_printhex(ps, arg);
	if (ps->conversion == 'u')
	{
		if (ps->width != 0)
			ft_putwidth(ps, 1, ft_nbrlen(arg));
		if (ps->precision != 0)
			ft_putprec(ps, ft_nbrlen(arg));
		if (!(ps->precision == -1 && arg == 0))
		{
			if (arg == 4294967295 || (long long)arg < 0)
				ps->ret += 10;
			else
				ps->ret += ft_nbrlen(arg);
			ft_putulnbr(arg);
		}
		if (ps->flags[1] == '1')
			ft_putwidth(ps, 0, ft_nbrlen(arg));
	}
}
