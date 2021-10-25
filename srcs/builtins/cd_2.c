/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:31:34 by fballest          #+#    #+#             */
/*   Updated: 2021/10/25 09:55:43 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_take_envs_free(t_env *env)
{
	int		i;

	i = 0;
	free (env->pwd);
	free (env->oldpwd);
	while (env->envp[i])
	{
		if (ft_strncmp("PWD=", env->envp[i], 4) == 0)
			env->pwd = ft_strchr2(env->envp[i], '=');
		if (ft_strncmp("OLDPWD=", env->envp[i], 7) == 0)
			env->oldpwd = ft_strchr2(env->envp[i], '=');
		i++;
	}
}

char	**ft_change_env(t_env *env)
{
	int		i;
	int		ok;
	char	**tmpenv;

	ok = 0;
	i = ft_matrixlen(env->envp);
	tmpenv = (char **)malloc(sizeof(char *) * (i + 1));
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
	ft_freematrix(env->envp);
	return (tmpenv);
}
