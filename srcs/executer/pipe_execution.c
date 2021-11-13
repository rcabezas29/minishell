/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:27:12 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/13 21:28:43 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_first_pipe(t_exe exe, t_env *env, int fd[])
{
	char	*path;
	char	**exeggutor;

	if (check_builtin(exe.cmd))
		return ;
	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	path = cmd_path(env, exe.cmd);
	exeggutor = assign_arguments_with_cmd(exe);
	execve(path, exeggutor, env->envp);
}

void	execute_last_pipe(t_exe exe, t_env *env, int fd[])
{
	char	*path;
	char	**exeggutor;

	if (check_builtin(exe.cmd))
		return ;
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	path = cmd_path(env, exe.cmd);
	exeggutor = assign_arguments_with_cmd(exe);
	execve(path, exeggutor, env->envp);
}

void	execute_between_pipes(t_exe exe, t_env *env, int read_fd[], int write_fd[])
{
	char	*path;
	char	**exeggutor;

	if (check_builtin(exe.cmd))
		return ;
	dup2(read_fd[READ_END], STDIN_FILENO);
	close(read_fd[READ_END]);
	dup2(write_fd[WRITE_END], STDOUT_FILENO);
	close(write_fd[WRITE_END]);
	path = cmd_path(env, exe.cmd);
	exeggutor = assign_arguments_with_cmd(exe);
	execve(path, exeggutor, env->envp);
}
