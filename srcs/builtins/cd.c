/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:36:49 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/14 10:39:13 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_cd(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;
	int		nargs;
	char	*tmp;	

	tmp = NULL;
	aux = cmd_info->command_list;
	nargs = count_arguments(aux);
	if (nargs > 1)
		aux = aux->next;
	if (nargs == 1)
	{
		env->oldpwd = env->pwd;
		env->pwd = env->home;
		chdir(env->pwd);
	}
	else if (nargs > 1
		&& ft_strncmp(((t_node *)aux->content)->prompts, "-", 2) == 0)
	{
		if (!env->oldpwd)
		{
			perror("cd: OLDPWD not set");
			return ;
		}
		else
		{
			tmp = env->pwd;
			env->pwd = env->oldpwd;
			env->oldpwd = tmp;
			chdir(env->pwd);
			printf("%s\n", env->pwd);
		}
	}
	else if (nargs > 1
		&& ft_strncmp(((t_node *)aux->content)->prompts, "~", 2) == 0)
	{
		tmp = env->pwd;
		env->pwd = env->home;
		env->oldpwd = tmp;
		chdir(env->pwd);
	}
	else
	{
		tmp = NULL;
		if (open(((t_node *)aux->content)->prompts, O_RDONLY) < 0)
		{
			perror("no such file or directory");
			return ;
		}
		env->oldpwd = env->pwd;
		chdir(((t_node *)aux->content)->prompts);
		tmp = getcwd(tmp, 250);
		env->pwd = tmp;
	}
	ft_change_env(env);
}

char	*ft_strextract(const char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_strdup("");
	while (str[i] && str[i] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i++] = '=';
	ret[i] = '\0';
	return (ret);
}

void	ft_change_env(t_env *env)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp("OLDPWD=", env->envp[i], 7) == 0)
		{
			tmp2 = ft_strextract(env->envp[i]);
			tmp = ft_strjoin(tmp2, env->oldpwd);
			env->envp[i] = tmp;
			tmp = NULL;
			tmp2 = NULL;
			free (tmp);
			free (tmp2);
		}
		if (ft_strncmp("PWD=", env->envp[i], 4) == 0)
		{
			tmp2 = ft_strextract(env->envp[i]);
			tmp = ft_strjoin(ft_strextract(env->envp[i]), env->pwd);
			env->envp[i] = tmp;
			tmp = NULL;
			tmp2 = NULL;
			free (tmp);
			free (tmp2);
		}
		i++;
	}
}
