/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:36:49 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/15 14:30:52 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_cd(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;
	int		nargs;
	int		i;
	char	tmp[FILENAME_MAX];	

	aux = cmd_info->command_list;
	nargs = count_arguments(aux);
	getcwd(env->pwd, FILENAME_MAX);
	if (nargs > 1)
		aux = aux->next;
	if (nargs == 1 || (nargs > 1
			&& ft_strncmp(((t_node *)aux->content)->prompts, "~", 2) == 0))
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
			i = 0;
			while (*env->oldpwd)
			{
				tmp[i] = *env->oldpwd;
				i++;
				env->oldpwd++;
			}
			env->oldpwd = env->pwd;
			env->pwd = tmp;
			chdir(env->pwd);
			printf("%s\n", env->pwd);
		}
	}
	else
	{
		ft_bzero(tmp, FILENAME_MAX);
		if (open(((t_node *)aux->content)->prompts, O_RDONLY) < 0)
		{
			perror("no such file or directory");
			return ;
		}
		env->oldpwd = env->pwd;
		chdir(((t_node *)aux->content)->prompts);
		getcwd(tmp, FILENAME_MAX);
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
	int		ok;
	char	*tmp;
	char	*tmp2;

	i = 0;
	ok = 0;
	while (env->envp[i])
	{
		if (ft_strncmp("PWD=", env->envp[i], 4) == 0)
		{
			tmp = ft_strjoin("PWD=", env->pwd);
			env->envp[i] = tmp;
			free (tmp);
			tmp = NULL;
		}
		if (ft_strncmp("OLDPWD", env->envp[i], 6) == 0)
		{
			ok += 1;
			tmp2 = ft_strjoin("OLDPWD=", env->oldpwd);
			env->envp[i] = tmp2;
		}
		i++;
	}
	if (ok == 0)
	{
		tmp2 = ft_strjoin("OLDPWD=", env->oldpwd);
		env->envp[i] = tmp2;
	}
	free (tmp2);
	tmp2 = NULL;
}
