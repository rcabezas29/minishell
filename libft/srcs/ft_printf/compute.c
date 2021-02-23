/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:33:14 by rcabezas          #+#    #+#             */
/*   Updated: 2020/09/09 09:27:04 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_castsgn(t_struct *ps, va_list ap)
{
	int nb;

	nb = va_arg(ap, int);
	if (nb < 0)
		ft_printsgn_neg(ps, nb);
	else
		ft_printsgn(ps, nb);
}

void		ft_compute(t_struct *ps, va_list ap)
{
	if (ps->conversion == 'd' || ps->conversion == 'i')
		ft_castsgn(ps, ap);
	else if (ps->conversion == 'u' || ps->conversion == 'x' ||
				ps->conversion == 'X')
		ft_printuns(ps, va_arg(ap, unsigned int));
	else if (ps->conversion == 's')
		ft_printstr(ps, va_arg(ap, char *));
	else if (ps->conversion == 'c')
		ft_printchar(ps, va_arg(ap, int));
	else if (ps->conversion == 'p')
		ft_printptr(ps, va_arg(ap, intptr_t));
	else if (ps->conversion == '%')
		ft_printpercent(ps);
}
