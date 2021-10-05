/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:36:49 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/05 15:16:20 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_createcdpath(char **tmp, t_env *env)
{
	char	*aux;
	char	*path;
	char 	*aux2;

	path = *tmp;
	while (*tmp)
	{
		if (!path)
			path = ft_strjoin(*tmp, "/");
		if (((*tmp)++))
		{
			aux = ft_strjoin(path, *tmp);
			free (path);
		}
		path = ft_strjoin(aux, "/");
		free (aux);
		(*tmp)++;
	}
	env->oldpwd = env->pwd;
	env->pwd = ft_strdup(path);
}

void	manage_points(char *arg, t_env *env)
{
	char	**tmp;

	
	if (arg[0] == '.' && arg[1] == '.')
	{
		if (!arg[2] && env->pwd != '/')
		{
			tmp = ft_split(env->pwd, "/");
			if (!ft_strncmp(*tmp, "/", 2))
			{
				env->oldpwd = env->pwd;
				env->pwd = "/";
			}
			while (*tmp)
				(*tmp)++;
			*tmp = NULL;
			ft_createcdpath(tmp, env);
		}
		else if (arg[2] == '/')
		{
			i = 2;
			while (arg[i] == '/')
				i++;
		}
		}
	}
}

void	execute_cd(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;
	int		nargs;
	char	*path;

	aux = cmd_info->command_list->next;
	nargs = count_arguments(aux);
	if (nargs > 2)
	{
		perror("string not in pwd");
		return ;
	}
	else if (nargs == 1)
	{
		env->pwd = ft_strdup(env->home);
		return ;
	}
	else
	{
		if (((t_node *)aux->content)->prompts[0] == '/')
		{
			path = ft_strdup(((t_node *)aux->content)->prompts);
			if (open(path, O_RDONLY) < 0)
			{
				perror("no such file or directory");
				return ;
			}
			env->oldpwd = env->pwd;
		}
		else if (((t_node *)aux->content)->prompts[0] == '.')
		{
			manage_points(((t_node *)aux->content)->prompts, env);
		}
		else if (((t_node *)aux->content)->prompts[0] == '-'
			&& !((t_node *)aux->content)->prompts[1])
		{
			path = env->oldpwd;
			env->oldpwd = env->pwd;
			env->pwd = ft_strdup(path);
			printf("%s\n", env->pwd);
			return ;
		}
		else if (((t_node *)aux->content)->prompts[0] == '~'
			&& !((t_node *)aux->content)->prompts[1])
		{
			path = env->home;
			env->oldpwd = env->pwd;
			env->pwd = ft_strdup(path);
			return ;
		}
		else
		{
			if (!((t_node *)aux->content)->prompts)
			{
				path = env->home;
				env->oldpwd = env->pwd;
				env->pwd = ft_strdup(path);
				return ;
			}
			else
			{
				path = ft_strdup(((t_node *)aux->content)->prompts);
				if (open(path, O_RDONLY) < 0)
				{
					perror("no such file or directory");
					return ;
				}
			}	
		}
		
	}
}