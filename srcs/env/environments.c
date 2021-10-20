/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:26:38 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/20 11:03:00 by fballest         ###   ########.fr       */
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

char	**add_basic_envs(char **envp)
{
	char	buff[FILENAME_MAX];
	char	**dst;
	int		i;
	int		x;

	i = 0;
	x = find_initial_envs(envp);
	dst = (char **)malloc(sizeof(char *) * (ft_arraylines(envp) + x));
	while (envp[i])
	{
		dst[i] = ft_strdup(envp[i]);
		i++;
		dst[i] = NULL;
	}
	if (!find_oldpwd(envp))
	{
		dst[i] = ft_strdup("OLDPWD");
		i++;
	}
	if (!find_pwd(envp))
	{
		getcwd(buff, sizeof(buff));
		dst[i] = ft_strjoin("PWD=", buff);
		i++;
	}
	if (!find_shlvl(envp))
	{
		dst[i] = ft_strdup("SHLVL=1");
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

void	take_envs(char	**envp, t_env *env)
{
	int		i;

	i = 0;
	env->envp = add_basic_envs(envp);
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
		if (ft_strncmp("OLDPWD", envp[i], 7) == 0)
			env->oldpwd = NULL;
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
