/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbrutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:12:51 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/05 11:22:14 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen(long long int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	if (n == 0)
		return (1);
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

void	ft_putulnbr(unsigned long long n)
{
	if (n > 9)
		ft_putulnbr(n / 10);
	ft_putchar_fd(n % 10 + '0', 1);
}

int	ft_nbrlen_base(long long int nb, char *base)
{
	size_t	i;

	i = 0;
	if ((size_t)nb >= ft_strlen(base))
		i += ft_nbrlen_base(nb / ft_strlen(base), base);
	i++;
	return (i);
}

void	ft_putnbr_base(long long int nb, char *base)
{
	if ((size_t)nb >= ft_strlen(base))
		ft_putnbr_base(nb / ft_strlen(base), base);
	ft_putchar_fd(base[nb % ft_strlen(base)], 1);
}
