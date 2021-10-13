/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:36:49 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/13 10:36:18 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_createcdpath(char **tmp, t_env *env)
{
	char	*aux;
	char	*path;

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
	free(path);
}

void	manage_points(char *arg, t_env *env)
{
	char	**tmp;
	int		i;

	if (arg[0] == '.' && arg[1] == '.')
	{
		if (!arg[2] && !ft_strncmp(env->pwd, "/", ft_strlen(env->pwd)))
		{
			i = 2;
			while (arg[i] == '/')
				i++;
			tmp = ft_split(env->pwd, '/');
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
			while (arg[i] != ' ' || arg[i] != '\0')
			{
				env->oldpwd = env->pwd;
				*env->pwd++ = arg[i++];
			}
		}
	}
}

void	execute_cd(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;
	int		nargs;
	char	*path;

	aux = cmd_info->command_list;
	nargs = count_arguments(aux);
	if (nargs == 1)
	{
		env->oldpwd = env->pwd;
		env->pwd = env->home;
	}
	else
	{
		aux = aux->next;
		if (((t_node *)aux->content)->prompts[0] == '/'
			|| (((t_node *)aux->content)->prompts[0] != '.'
			&& ((t_node *)aux->content)->prompts[0] != '-'
			&& ((t_node *)aux->content)->prompts[0] != '~'))
		{
			path = ft_strdup(((t_node *)aux->content)->prompts);
			if (open(path, O_RDONLY) < 0)
			{
				perror("no such file or directory");
				return ;
			}
			else
			{
				env->oldpwd = env->pwd;
				env->pwd = path;
			}
		}
		else if (((t_node *)aux->content)->prompts[0] == '.')
		{
			manage_points(((t_node *)aux->content)->prompts, env);
			return ;
		}
		else if (((t_node *)aux->content)->prompts[0] == '-'
			&& !((t_node *)aux->content)->prompts[1])
		{
			path = env->oldpwd;
			env->oldpwd = env->pwd;
			env->pwd = path;
			printf("%s\n", env->pwd);
			return ;
		}
		else if (((t_node *)aux->content)->prompts[0] == '~'
			&& !((t_node *)aux->content)->prompts[1])
		{
			path = env->home;
			env->oldpwd = env->pwd;
			env->pwd = path;
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
			env->pwd = ft_strjoin(env->pwd, "/");
			env->pwd = ft_strjoin(env->pwd, path);
			free(path);
		}	
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

	i = 0;

	while (env->envp[i])
	{
		if (ft_strncmp("OLDPWD=", env->envp[i], 7) == 0)
		{
			tmp = env->envp[i];
			env->envp[i] = ft_strjoin(ft_strextract(tmp), env->oldpwd);
		}
		if (ft_strncmp("PWD=", env->envp[i], 4) == 0)
		{
			tmp = env->envp[i];
			env->envp[i] = ft_strjoin(ft_strextract(tmp), env->pwd);
		}
		i++;
	}
}
