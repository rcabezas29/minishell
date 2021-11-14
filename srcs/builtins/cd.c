/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:36:49 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/14 10:18:48 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd_alone(t_env *env)
{
	char	*tmp;

	tmp = ft_strdup(env->pwd);
	env->oldpwd = ft_strdup(tmp);
	env->pwd = ft_strdup(env->home);
	chdir(env->pwd);
	free(tmp);
}

int	cd_guion(t_env *env)
{
	char	*tmp;

	tmp = NULL;
	if (!env->oldpwd)
	{
		printf("cd: OLDPWD not set\n");
		return (1);
	}
	else
	{
		tmp = ft_strdup(env->pwd);
		env->pwd = ft_strdup(env->oldpwd);
		env->oldpwd = ft_strdup(tmp);
		free (tmp);
		chdir(env->pwd);
		printf("%s\n", env->pwd);
		return (0);
	}
}

int	cd_path(t_env *env, t_exe exe)
{
	char	tmp[FILENAME_MAX];

	if (open(exe.args[0], O_RDONLY) < 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", exe.args[0]);
		return (1);
	}
	env->oldpwd = ft_strdup(env->pwd);
	chdir(exe.args[0]);
	getcwd(tmp, FILENAME_MAX);
	env->pwd = ft_strdup(tmp);
	return (0);
}

int		execute_cd(t_exe exe, t_env *env)
{
	int		nargs;

	nargs = ft_matrixlen(exe.args);
	getcwd(env->pwd, FILENAME_MAX);
	if (nargs == 0 || (nargs > 0
			&& ft_strncmp(exe.args[0], "~", 2) == 0))
		cd_alone(env);
	else if (nargs > 1
		&& ft_strncmp(exe.args[0], "-", 2) == 0)
		return (cd_guion(env));
	else
		cd_path(env, exe);
	env->envp = ft_change_env(env);
	ft_take_envs_free(env);
	return (0);
}
