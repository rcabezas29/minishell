/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:38:39 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/18 12:08:49 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_env(t_env *env)
{
	int		i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strchr(env->envp[i], '='))
			printf("%s\n", env->envp[i]);
		i++;
	}
}
