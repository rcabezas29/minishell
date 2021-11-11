/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:55:10 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/11 21:12:49 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**assign_arguments_with_cmd(t_cmd_info *cmd_info)
{
	
}

int		check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

int	execute_simple_commands(t_cmd_info *cmd_info, t_env *env)
{
	char			*path;
	int				pid;
	char			**exeggutor;
	int				j;
	int				ret;

	if (check_builtin(cmd_info->exe[0].cmd))
	{
		execute_builtins(cmd_info, env);
		return (cmd_info->return_code);
	}
	else
	{
		j = 0;
		path = cmd_path(env, cmd_info->exe[0].cmd);
		exeggutor = assign_arguments_with_cmd(tmp);
		pid = fork();
		if (pid == 0)
		{
			son_signal();
			ret = execve(path, exeggutor, env->envp);
			ft_freematrix(exeggutor);
			free(path);
			exit(ret);
		}
		else
		{
			waitpid(pid, &j, 0);
			free(path);
			path = NULL;
			ft_freematrix(exeggutor);
		}
		return (j % 255);
	}
}