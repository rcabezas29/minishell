/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:36:49 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/16 15:01:27 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cd_alone(t_env *env)
{
	char	*tmp;

	if (!env->home)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	tmp = ft_strdup(env->pwd);
	env->oldpwd = ft_strdup(tmp);
	env->pwd = ft_strdup(env->home);
	chdir(env->pwd);
	free(tmp);
	return (0);
}

int	cd_guion(t_env *env)
{
	char	*tmp;

	tmp = NULL;
	if (!env->oldpwd)
	{
		write(2, "cd: OLDPWD not set\n", 19);
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
		write(2, "minishell: cd: ", 15);
		write(2, exe.args[0], ft_strlen(exe.args[0]));
		write(2, ": No such file or directory\n", 28);
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
	int		ret;
	char	*tmp;

	tmp = NULL;
	nargs = ft_matrixlen(exe.args);
	getcwd(tmp, FILENAME_MAX);
	env->pwd = ft_strdup(tmp);
	if (nargs == 0 || (nargs > 0
			&& ft_strncmp(exe.args[0], "~", 2) == 0))
		ret = cd_alone(env);
	else if (nargs > 1
		&& ft_strncmp(exe.args[0], "-", 2) == 0)
		ret = cd_guion(env);
	else
		ret = cd_path(env, exe);
	ft_change_env(env);
	ft_take_envs_free(env);
	return (ret);
}
