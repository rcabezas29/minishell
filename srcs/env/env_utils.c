/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:32:34 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/02 18:53:57 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	change_shlvl(t_env *env)
{
	int	level;
	int	i;
	char	*level_str;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp("SHLVL=", env->envp[i], 6) == 0)
		{
			level_str = ft_strchr2(env->envp[i], '=');
			level = ft_atoi(level_str);
			level += 1;
			free(env->envp[i]);
			env->envp[i] = ft_strjoin("SHLVL=", ft_itoa(level));
		}
		i++;
	}
}

void	add_slash_to_path(t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env->paths[i])
	{
		tmp = ft_strjoin(env->paths[i], "/");
		free(env->paths[i]);
		env->paths[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
}
