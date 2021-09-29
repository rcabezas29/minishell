/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:15:28 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/29 13:44:54 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_arguments(t_list *tmp)
{
	t_list	*aux;
	int		i;

	aux = tmp;
	i = 1;
	while (((t_node *)aux->next) && ((t_node *)aux->content)->types == ARGUMENT)
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
		free(((t_node *)tmp->content)->prompts);
		((t_node *)tmp->content)->prompts = NULL;
		ft_lstdelone(tmp, free);
		tmp = tmp->next;
		i++;
		ret[i] = NULL;
	}
	return (ret);
}

void	ft_freearray(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	execute_paths(t_list *tmp, t_env *env)
{
	char	*path;
	int		pid;
	char	**exeggutor;

	path = cmd_path(env, (char *)((t_node *)tmp->content)->prompts);
	exeggutor = assign_arguments_for_execve(tmp);
	pid = fork();
	if (pid == 0)
	{
		execve(path, exeggutor, env->envp);
		free(path);
		ft_freearray(exeggutor);
	}
	free(path);
	ft_freearray(exeggutor);
	
}

void	execute(t_cmd_info *cmd_info, t_env *env)
{
	int	i;
	t_list	*tmp;

	i = 0;
	tmp = cmd_info->command_list;
	while (i <= cmd_info->no_pipes)
	{
		if (((t_node *)tmp->content)->types == 0)
		{
			if (((t_node *)tmp->content)->built_in == 1)
				continue; 
				//execute_builtins(cmd_info);
			else
			{
				execute_paths(tmp, env);
				break ;
			}
		}
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
		tmp = ft_strjoin((char *)env->paths[i], cmd);
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
			break ;
		}
	}
	if (!path)
	{
		tmp = ft_strjoin(cmd, ": command not found");
		ft_putstr(tmp);
		free(tmp);
		return (NULL);
	}
	return (path);
}

// FUNCION PARA DERIBAR LOS BUILTINS A SU FUNCION EJECUTABLE CORRESPONDIENTE
// void	execute_builtins(t_cmd_info *cmd_info)
// {
// 	t_list	*aux;

// 	aux = cmd_info->command_list;
// 	if (!ft_strcmp(((t_node *)aux->content)->prompts, "echo"))
// 		excute_echo(cmd_info);
// 	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "cd"))
// 		excute_cd(cmd_info);
// 	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "pwd"))
// 		excute_pwd(cmd_info);
// 	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "env"))
// 		excute_env(cmd_info);
// 	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "export"))
// 		excute_export(cmd_info);
// 	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "unset"))
// 		excute_unset(cmd_info);
// 	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "exit"))
// 		excute_exit(cmd_info);
// 	else
// 		perror("command not found");
// }
