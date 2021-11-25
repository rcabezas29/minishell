/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:20:01 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/25 13:28:42 by rcabezas         ###   ########.fr       */
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

void	close_pipes(int	**fd, int *saved_fds, int i,
			t_cmd_info *cmd_info)
{
	if (i == 0)
		close(fd[0][WRITE_END]);
	else if (i == cmd_info->no_pipes)
	{
		close(fd[i - 1][READ_END]);
		dup2(saved_fds[STDIN_FILENO], STDIN_FILENO);
		close(saved_fds[STDIN_FILENO]);
		dup2(saved_fds[STDOUT_FILENO], STDOUT_FILENO);
		close(saved_fds[STDOUT_FILENO]);
	}
	else
	{
		close(fd[i - 1][READ_END]);
		close(fd[i][WRITE_END]);
	}
}

void	pipe_execution(t_cmd_info *cmd_info, t_env *env, int **fd)
{
	int	saved_fds[2];
	int	pid;
	int	i;

	saved_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	saved_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
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
			close_pipes(fd, saved_fds, i, cmd_info);
		i++;
	}
}

int	execute_pipes(t_cmd_info *cmd_info, t_env *env)
{
	int		i;
	int		**fd;

	fd = malloc(sizeof(int *) * cmd_info->no_pipes);
	i = 0;
	while (i < cmd_info->no_pipes)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe(fd[i]);
		i++;
	}
	pipe_execution(cmd_info, env, fd);
	cmd_info->return_code = waiting_room(cmd_info->no_pipes);
	i = 0;
	while (i < cmd_info->no_pipes)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	return (cmd_info->return_code);
}
