/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnegsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 17:21:13 by rcabezas          #+#    #+#             */
/*   Updated: 2020/09/09 09:27:31 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putlnbr(long long int n)
{
	if (n <= -2147483648)
	{
		ft_putstr_fd("2147483648", 1);
		return ;
	}
	if (n < 0)
		n = -n;
	if (n > 9)
		ft_putlnbr(n / 10);
	ft_putchar_fd(n % 10 + '0', 1);
}

static void	ft_putwidth(t_struct *ps, int less, int arglen)
{
	int	i;
	int	widthlen;
	int	preclen;

	i = 0;
	widthlen = ps->precision == -1 && ps->width >= 0 ?
				ps->width - (2 * arglen) : ps->width - arglen;
	if (ps->precision == -1)
		widthlen += arglen;
	preclen = ps->precision >= arglen ? ps->precision - arglen + 1 : 0;
	if (ps->width > 0 && ((less == 0 && ps->flags[1] == '1') ||
				(less != 0 && ps->flags[1] != '1')))
	{
		while (++i <= widthlen - preclen)
		{
			if (ps->precision == 0 || ps->precision < -1)
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
	preclen = ps->precision >= arglen ? ps->precision - arglen + 1 : 0;
	if (ps->precision > 0)
	{
		while (++i <= preclen)
			ft_putchar_fd('0', 1);
		ps->ret += i - 1;
	}
}

static void	negative_width(int i, t_struct *ps, long long int arg)
{
	while (i++ < (-1 * ps->width) - ft_nbrlen(arg))
		ft_putchar_fd(' ', 1);
	ps->ret += i - 1;
}

void		ft_printsgn_neg(t_struct *ps, long long int arg)
{
	size_t	arglen;
	int		i;

	i = 0;
	arglen = ft_nbrlen(arg);
	if (ps->flags[0] == '1' && ps->precision == 0)
		ft_putchar_fd('-', 1);
	if (ps->width > 0)
		ft_putwidth(ps, 1, arglen);
	if ((ps->flags[0] == '1' && (ps->precision > 0 || ps->precision == -1)) ||
				ps->flags[0] == '0')
		ft_putchar_fd('-', 1);
	if (ps->precision > 0)
		ft_putprec(ps, arglen);
	if ((ps->precision == -1 && ps->width >= 0) || ps->precision != -1)
	{
		ps->ret += arglen;
		ft_putlnbr(arg);
	}
	if (ps->flags[1] == '1')
		ft_putwidth(ps, 0, arglen);
	if (ps->width < 0)
		negative_width(i, ps, arg);
}
