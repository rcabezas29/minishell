/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:09:10 by rcabezas          #+#    #+#             */
/*   Updated: 2020/11/04 19:03:43 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*a;

	if (nitems == 0 || size == 0)
		nitems = size - 1;
	if (!(a = (char *)malloc(nitems * size)))
		return (0);
	ft_bzero(a, nitems * size);
	return (a);
}
