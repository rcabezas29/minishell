/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:20:01 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/24 11:19:45 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	waiting_room(int no_pipes)
{
	int	i;
	int	j;

	i = 0;
	while (i <= no_pipes)
	{
		waitpid(-1, &j, 0);
		i++;
	}
	return (j);
}

void	close_pipes(int	**fd, int saved_stdin, int saved_stdout, int i, t_cmd_info *cmd_info)
{
	if (i == 0)
		close(fd[0][WRITE_END]);
	else if (i == cmd_info->no_pipes)
	{
		close(fd[i - 1][READ_END]);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	else
	{
		close(fd[i - 1][READ_END]);
		close(fd[i][WRITE_END]);
	}
}

int	execute_pipes(t_cmd_info *cmd_info, t_env *env)
{
	int		i;
	pid_t	pid;
	int		**fd;
	int		saved_stdout;
	int		saved_stdin;

	i = 0;
	fd = malloc(sizeof(int *) * cmd_info->no_pipes);
	while (i < cmd_info->no_pipes)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe(fd[i]);
		i++;
	}
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	i = 0;
	while (i <= cmd_info->no_pipes)
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
		}
		else
			close_pipes(fd, saved_stdin, saved_stdout, i, cmd_info);
		i++;
	}
	cmd_info->return_code = waiting_room(cmd_info->no_pipes);
	return (cmd_info->return_code);
}
