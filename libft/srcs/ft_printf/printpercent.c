/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printpercent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 17:12:19 by rcabezas          #+#    #+#             */
/*   Updated: 2020/09/09 09:27:35 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putpads(t_struct *ps, int less)
{
	int	i;
	int	widthlen;

	i = 0;
	widthlen = ps->width - 1;
	if (ps->width > 0 && ((less != 0 && ps->flags[1] == '1') ||
				(less == 0 && ps->flags[1] == '0')))
	{
		while (++i <= widthlen)
			ft_putchar_fd(ps->flags[0] == '1' && ps->flags[1] == '0' ?
						'0' : ' ', 1);
		ps->ret += i - 1;
	}
}

void		ft_printpercent(t_struct *ps)
{
	if (ps->width > 0 || ps->precision > 0)
		ft_putpads(ps, 0);
	ps->ret++;
	ft_putchar_fd('%', 1);
	if (ps->flags[1] == '1')
		ft_putpads(ps, 1);
}
