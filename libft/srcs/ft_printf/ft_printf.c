/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 17:23:28 by rcabezas          #+#    #+#             */
/*   Updated: 2020/09/09 09:26:51 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_read(t_struct *ps, const char *format, va_list ap)
{
	while (format[ps->i])
	{
		if (format[ps->i] == '%')
		{
			ps->i++;
			if (ft_parse(ps, format, ap))
				ft_compute(ps, ap);
			ft_reinit(ps);
		}
		else
		{
			ft_putchar_fd(format[ps->i], 1);
			ps->i++;
			ps->ret++;
		}
	}
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_struct	*ps;
	size_t		ret;

	if (!format)
		return (-1);
	if (!(ps = malloc(sizeof(t_struct))) || !(ft_init(ps)))
		return (-1);
	va_start(ap, format);
	ft_read(ps, format, ap);
	ret = ps->ret;
	free(ps);
	return (ret);
}
