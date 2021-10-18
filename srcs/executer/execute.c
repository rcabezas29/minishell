/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:15:28 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/18 16:35:35 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_arguments(t_list *tmp)
{
	t_list	*aux;
	int		i;

	aux = tmp;
	i = 0;
	while (((t_node *)aux) && ((t_node *)aux->content)->types == ARGUMENT)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

char	**assign_arguments_for_execve(t_list *tmp)
{
	char	**ret;
	int		i;
	int		narg;

	narg = count_arguments(tmp);
	ret = NULL;
	ret = (char **)malloc(sizeof(char *) * (narg + 1));
	i = 0;
	while (i < narg)
	{
		ret[i] = ft_strdup(((t_node *)tmp->content)->prompts);
		tmp = tmp->next;
		i++;
		ret[i] = NULL;
	}
	return (ret);
}

void	execute_paths(t_list *tmp, t_env *env)
{
	char	*path;
	int		pid;
	char	**exeggutor;
	int		j;

	path = cmd_path(env, (char *)((t_node *)tmp->content)->prompts);
	exeggutor = assign_arguments_for_execve(tmp);
	pid = fork();
	if (pid == 0)
	{
		execve(path, exeggutor, env->envp);
		exit(0);
	}
	else
	{
		waitpid(pid, &j, 0);
		free(path);
		path = NULL;
		ft_freematrix(exeggutor);
	}
}

void	execute(t_cmd_info *cmd_info, t_env *env)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = cmd_info->command_list;
	while (i <= cmd_info->no_pipes)
	{
		if (((t_node *)tmp->content)->types == 0)
		{
			if (((t_node *)tmp->content)->built_in == 1)
				execute_builtins(cmd_info, env);
			else
			{
				execute_paths(tmp, env);
				break ;
			}
		}
		i++;
	}
}

char	*cmd_path(t_env *env, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;
	int		check_path;

	path = NULL;
	i = 0;
	if (open(cmd, O_RDONLY) >= 0)
		return (cmd);
	while (env->paths[i])
	{
		tmp = ft_strjoin(env->paths[i], cmd);
		check_path = open(tmp, O_RDONLY);
		if (check_path < 0)
		{
			free(tmp);
			i++;
		}
		else
		{
			path = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
			break ;
		}
	}
	if (!path)
	{
		tmp = ft_strjoin(cmd, ": command not found\n");
		ft_putstr(tmp);
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	return (path);
}

void	execute_builtins(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;

	aux = cmd_info->command_list;
	ft_strdowncase(((t_node *)aux->content)->prompts);
	if (!ft_strcmp(((t_node *)aux->content)->prompts, "echo"))
		execute_echo(cmd_info);
	if (!ft_strcmp(((t_node *)aux->content)->prompts, "cd"))
		execute_cd(cmd_info, env);
	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "pwd"))
		execute_pwd(cmd_info);
	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "env"))
		execute_env(env);
 	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "export"))
 		execute_export(cmd_info, env);
	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "unset"))
		execute_unset(cmd_info, env);
 	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "exit"))
 		execute_exit(cmd_info, env);
	//	perror("command not found");
}
