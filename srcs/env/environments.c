/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:26:38 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/18 12:18:52 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strchr2(const char *str, char c)
{
	int				i;
	unsigned char	ch;
	char			*p;

	i = 0;
	p = (char *)str;
	ch = c + '\0';
	while (p[i] != '\0')
	{
		if (p[i] == ch)
			return (p + i + 1);
		i++;
	}
	if (ch == '\0')
		return (p + i + 1);
	return (0);
}

int	ft_arraylines(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	take_envs(char	**envp, t_env *env)
{
	int		i;

	i = 0;
	env->envp = (char **)malloc(sizeof(char *) * (ft_arraylines(envp) + 1));
	while (envp[i])
	{
		env->envp[i] = ft_strdup(envp[i]);
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
	env->envp[i] = NULL;
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
