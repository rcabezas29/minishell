/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:41:23 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/05 12:38:29 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
			widthlen = ps->precision < arglen ?
						ps->width - ps->precision : ps->width - arglen;
	}
	else if (ps->precision == 0 && ps->width != 0)
		widthlen = ps->width - arglen;
	else
		widthlen = 0;
	if (ps->precision == -1)
		widthlen += ps->width;
	if (ps->width != 0 && ((less == 0 && ps->flags[1] == '1') ||
				(less != 0 && ps->flags[1] == '0')))
	{
		while (++i <= widthlen)
			ft_putchar_fd(ps->flags[0] == '1' && less != 0 ? '0' : ' ', 1);
		ps->ret += i - 1;
	}
}

static void	no_prec_but_width_and_negwidthprec0(int i, t_struct *ps, char *arg)
{
	if (ps->width < 0 && ps->precision == 0)
	{
		while (i-- > ps->width + (int)ft_strlen((const char *)arg))
		{
			ft_putchar_fd(' ', 1);
			ps->ret++;
		}
	}
	if (ps->width < 0 && ps->precision == -1)
	{
		while (i++ < (-ps->width))
			ft_putchar_fd(' ', 1);
		ps->ret += i - 1;
	}
}

static void	neg_prec_width(int i, t_struct *ps, char *arg)
{
	while (i++ < (-ps->width - (int)ft_strlen((const char *)arg)))
		ft_putchar_fd(' ', 1);
	ps->ret += i - 1;
}

static void	write4noprec(char *arg, t_struct *ps)
{
	ft_putstr_fd(arg, 1);
	ps->ret += ft_strlen(arg);
}

void		ft_printstr(t_struct *ps, char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		arg = "(null)";
	if (ps->width > 0 || ps->precision > 0)
		ft_putpads(ps, 1, ft_strlen(arg));
	if (ps->precision != 0 && ps->precision != -1)
	{
		while (i != ps->precision && arg[i])
			ft_putchar_fd(arg[i++], 1);
		ps->ret += i;
	}
	else if (ps->precision != -1)
		write4noprec(arg, ps);
	i = 0;
	if (ps->width < 0 && ps->precision < 0 && ps->width < ps->precision)
		neg_prec_width(i, ps, arg);
	if (ps->width != 0 && ps->flags[1] == '1')
		ft_putpads(ps, 0, ft_strlen(arg));
	if ((ps->width < 0 && ps->precision == 0) ||
				(ps->width < 0 && ps->precision == -1))
		no_prec_but_width_and_negwidthprec0(i, ps, arg);
}
