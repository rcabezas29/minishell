/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:31:34 by fballest          #+#    #+#             */
/*   Updated: 2021/11/19 01:34:12 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_take_envs_free(t_env *env)
{
	int		i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp("PWD=", env->envp[i], 4) == 0)
			env->pwd = ft_strchr2(env->envp[i], '=');
		if (ft_strncmp("OLDPWD=", env->envp[i], 7) == 0)
			env->oldpwd = ft_strchr2(env->envp[i], '=');
		i++;
	}
}

void	ft_change_env(t_env *env)
{
	int		i;
	int		ok;
	char	**tmpenv;

	ok = 0;
	i = ft_matrixlen(env->envp);
	tmpenv = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp("PWD=", env->envp[i], 4) == 0)
			tmpenv[i] = ft_strjoin("PWD=", env->pwd);
		else if (ft_strncmp("OLDPWD", env->envp[i], 6) == 0)
			tmpenv[i] = ft_strjoin("OLDPWD=", env->oldpwd);
		else
			tmpenv[i] = ft_strdup(env->envp[i]);
		i++;
	}
	tmpenv[i] = NULL;
	env->envp = ft_matrixdup(tmpenv);
	ft_freematrix(tmpenv);
}
