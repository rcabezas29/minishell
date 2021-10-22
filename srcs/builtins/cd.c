/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:36:49 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/22 13:53:07 by fballest         ###   ########.fr       */
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
	{
		tmp = ft_strdup(env->pwd);
		env->oldpwd = ft_strdup(tmp);
		env->pwd = ft_strdup(env->home);
		chdir(env->pwd);
		free(tmp);
	}
	else if (nargs > 1
		&& ft_strncmp(((t_node *)aux->content)->prompts, "-", 2) == 0)
	{
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
	else
	{
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
	env->envp = ft_change_env(env);
	ft_take_envs_free(env);
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

char	**ft_change_env(t_env *env)
{
	int		i;
	int		ok;
	char	**tmpenv;

	ok = 0;
	i = ft_matrixlen(env->envp);
	tmpenv = (char **)malloc(sizeof(char *) * (i + 2));
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
