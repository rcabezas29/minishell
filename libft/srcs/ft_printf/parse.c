/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:14:18 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/05 11:24:28 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_parseast(const char *format, t_struct *ps, va_list ap)
{
	if (format[ps->i] == '*' && format[ps->i - 1] == '.')
		ft_precisionast(ps, ap);
	else
		ft_widthast(ps, ap);
}

static void	ft_parseflags(t_struct *ps, const char *format)
{
	if (format[ps->i] == '0')
	{
		ps->flags[0] = '1';
		ps->i++;
	}
	if (format[ps->i] == '-')
	{
		ps->flags[1] = '1';
		ps->i++;
	}
}

static void	ft_parsespecs(t_struct *ps, const char *format, va_list ap)
{
	if (format[ps->i] == '0' || format[ps->i] == '-')
		ft_parseflags(ps, format);
	if ((ft_isdigit(format[ps->i]) && format[ps->i] != '0'))
		ft_parsewidth(ps, format, ap);
	if (format[ps->i] == '.')
		ft_parseprecision(ps, format, ap);
	if (format[ps->i] == '*')
		ft_parseast(format, ps, ap);
}

int	ft_parse(t_struct *ps, const char *format, va_list ap)
{
	while ((format[ps->i] == '0' || format[ps->i] == '-'
			|| format[ps->i] == '.' || ft_isdigit(format[ps->i])
			|| format[ps->i] == '*') && format[ps->i])
		ft_parsespecs(ps, format, ap);
	if (ps->precision == 0 && ps->dot == 1)
		ps->precision = -1;
	if (ft_charchr("cspdiuxX%", format[ps->i]))
		ps->conversion = format[ps->i++];
	return (1);
}
