/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 17:39:54 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/05 12:04:37 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_struct
{
	char		flags[2];
	int			width;
	int			precision;
	int			dot;
	char		modifier;
	char		conversion;
	size_t		ret;
	size_t		i;
}				t_struct;

int				ft_printf(const char *format, ...);

int				ft_init(t_struct *ps);
int				ft_reinit(t_struct *ps);

void			ft_compute(t_struct *ps, va_list ap);

int				ft_parse(t_struct *ps, const char *format, va_list ap);
void			ft_parsewidth(t_struct *ps, const char *format, va_list ap);
void			ft_parseprecision(t_struct *ps, const char *format, va_list ap);

void			ft_precisionast(t_struct *ps, va_list ap);
void			ft_widthast(t_struct *ps, va_list ap);

int				ft_nbrlen(long long int n);
void			ft_putulnbr(unsigned long long n);
int				ft_nbrlen_base(long long int nb, char *base);
void			ft_putnbr_base(long long int nb, char *base);

void			ft_printchar(t_struct *ps, char arg);
void			ft_printstr(t_struct *ps, char *arg);
void			ft_printsgn_neg(t_struct *ps, long long int arg);
void			ft_printsgn(t_struct *ps, long long int arg);
void			ft_printpercent(t_struct *ps);
void			ft_printptr(t_struct *ps, intptr_t arg);
void			ft_printuns(t_struct *ps, unsigned long long arg);

void			ft_putsharp(t_struct *ps);
int				ft_charchr(const char *s, int c);

void			put_s_or_z(t_struct *ps);
#endif
