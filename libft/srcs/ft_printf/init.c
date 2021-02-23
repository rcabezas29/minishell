/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:43:34 by rcabezas          #+#    #+#             */
/*   Updated: 2020/09/09 09:26:57 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_reinit(t_struct *ps)
{
	ft_bzero(ps->flags, 2);
	ps->width = 0;
	ps->precision = 0;
	ps->dot = 0;
	ps->modifier = '\0';
	ps->conversion = '\0';
	return (1);
}

int	ft_init(t_struct *ps)
{
	ft_bzero(ps->flags, 2);
	ps->width = 0;
	ps->precision = 0;
	ps->dot = 0;
	ps->modifier = '\0';
	ps->conversion = '\0';
	ps->ret = 0;
	ps->i = 0;
	return (1);
}
