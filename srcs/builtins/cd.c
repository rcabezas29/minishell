/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:36:49 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/22 14:32:16 by fballest         ###   ########.fr       */
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

void	cd_guion(t_env *env, t_cmd_info *cmd_info)
{
	char	*tmp;

	tmp = NULL;
	if (!env->oldpwd)
	{
		printf("cd: OLDPWD not set\n");
		cmd_info->return_code = 1;
		return ;
	}
	else
	{
		tmp = ft_strdup(env->pwd);
		env->pwd = ft_strdup(env->oldpwd);
		env->oldpwd = ft_strdup(tmp);
		free (tmp);
		chdir(env->pwd);
		printf("%s\n", env->pwd);
	}
}

void	cd_path(t_env *env, t_list *aux, t_cmd_info *cmd_info)
{
	char	*tmp;

	tmp = NULL;
	if (open(((t_node *)aux->content)->prompts, O_RDONLY) < 0)
	{
		printf("minishell: cd: %s: No such file or directory\n",
			((t_node *)aux->content)->prompts);
		cmd_info->return_code = 1;
		return ;
	}
	tmp = ft_strdup(env->pwd);
	env->oldpwd = ft_strdup(tmp);
	free (tmp);
	chdir((char *)((t_node *)aux->content)->prompts);
	getcwd(tmp, FILENAME_MAX);
	env->pwd = ft_strdup(tmp);
}

void	execute_cd(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;
	int		nargs;
	char	*tmp;	

	aux = cmd_info->command_list;
	nargs = count_arguments(aux);
	tmp = NULL;
	getcwd(env->pwd, FILENAME_MAX);
	if (nargs > 1)
		aux = aux->next;
	if (nargs == 1 || (nargs > 1
			&& ft_strncmp(((t_node *)aux->content)->prompts, "~", 2) == 0))
		cd_alone(env);
	else if (nargs > 1
		&& ft_strncmp(((t_node *)aux->content)->prompts, "-", 2) == 0)
		cd_guion(env, cmd_info);
	else
		cd_path(env, aux, cmd_info);
	env->envp = ft_change_env(env);
	ft_take_envs_free(env);
}
