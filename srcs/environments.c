/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:26:38 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/14 09:30:20 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*take_envs(char	**envp)
{
	int	i;
	t_env	*env;

	i = 0;
	env = ft_calloc(sizeof(t_env), 1);
	env->envp = envp;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			env->paths = ft_split(ft_strchr(envp[i], '/'), ':');
		if (ft_strncmp("USER=", envp[i], 5) == 0)
			env->user = ft_strchr(envp[i], '=');
		if (ft_strncmp("HOME=", envp[i], 5) == 0)
			env->home = ft_strchr(envp[i], '=');
		if (ft_strncmp("PWD=", envp[i], 5) == 0)
			env->pwd = ft_strchr(envp[i], '=');
		i++;
	}
	return (env);
}
