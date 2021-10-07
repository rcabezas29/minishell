/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:26:38 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/07 12:51:50 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strchr2(const char *str, char c)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = ft_strdup("");
	while (str[i] != c)
		i++;
	i++;
	while (str[i] != '\0')
	{
		ret[j++] = str[i++];
	}
	ret[j] = '\0';
	return (ret);
}

void	take_envs(char	**envp, t_env *env)
{
	int		i;

	i = 0;
	env->envp = envp;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			env->paths = ft_split(ft_strchr(envp[i], '/'), ':');
			add_slash_to_path(env);
		}
		if (ft_strncmp("USER=", envp[i], 5) == 0)
			env->user = ft_strchr2(envp[i], '=');
		if (ft_strncmp("HOME=", envp[i], 5) == 0)
			env->home = ft_strchr2(envp[i], '=');
		if (ft_strncmp("PWD=", envp[i], 4) == 0)
			env->pwd = ft_strchr2(envp[i], '=');
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
