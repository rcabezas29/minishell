/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:20:01 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/13 15:53:19 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	waiting_room(void)
{
	int	j;
	
	j = 0;
	waitpid(-1, &j, 0);
	return (j);
}

int	execute_pipes(t_cmd_info *cmd_info, t_env *env)
{
	int		i;
	pid_t	pid;
	int	fd[cmd_info->no_pipes][2];

	i  = 0;
	while (i < cmd_info->no_pipes)
	{
		pipe(fd[i]);
		i++;
	}
	i  = 0;
	while (i < cmd_info->no_pipes)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				execute_first_pipe(cmd_info->exe[i], env, fd[i]);
			else if (i == cmd_info->no_pipes)
				execute_last_pipe(cmd_info->exe[i], env, fd[i - 1]);
			else
				execute_between_pipes(cmd_info->exe[i], env, fd[i - 1], fd[i]);
			i++;
		}
		else
			i++;
	}
	cmd_info->return_code = waiting_room();
	return (cmd_info->return_code);
}
