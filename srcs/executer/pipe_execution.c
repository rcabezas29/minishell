/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:27:12 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/14 13:32:11 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_first_pipe(t_exe exe, t_env *env, int fd[])
{
	char	*path;
	char	**exeggutor;
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (exe.fd_in)
	{
		dup2(exe.fd_in, STDIN_FILENO);
		close(exe.fd_in);
	}
	if (exe.fd_out)
	{
		dup2(exe.fd_out, STDOUT_FILENO);
		close(exe.fd_out);
	}
	else
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
	}
	if (check_builtin(exe.cmd))
	{
		execute_builtins(exe, env);
		exit(EXIT_SUCCESS);
	}
	path = cmd_path(env, exe.cmd);
	exeggutor = assign_arguments_with_cmd(exe);
	execve(path, exeggutor, env->envp);
}

void	execute_last_pipe(t_exe exe, t_env *env, int fd[])
{
	char	*path;
	char	**exeggutor;
	int		return_code;

	if (exe.fd_out)
	{
		dup2(exe.fd_out, STDOUT_FILENO);
		close(exe.fd_out);
	}
	if (exe.fd_in)
	{
		dup2(exe.fd_in, STDIN_FILENO);
		close(exe.fd_in);
	}
	else
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
	}
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	if (check_builtin(exe.cmd))
	{
		return_code = execute_builtins(exe, env);
		exit(EXIT_SUCCESS);
	}
	path = cmd_path(env, exe.cmd);
	exeggutor = assign_arguments_with_cmd(exe);
	execve(path, exeggutor, env->envp);
}

void	execute_between_pipes(t_exe exe, t_env *env, int read_fd[],
			int write_fd[])
{
	char	*path;
	char	**exeggutor;

	dup2(read_fd[READ_END], STDIN_FILENO);
	close(read_fd[READ_END]);
	dup2(write_fd[WRITE_END], STDOUT_FILENO);
	close(write_fd[WRITE_END]);
	if (check_builtin(exe.cmd))
	{
		execute_builtins(exe, env);
		exit(EXIT_SUCCESS);
	}
	path = cmd_path(env, exe.cmd);
	exeggutor = assign_arguments_with_cmd(exe);
	execve(path, exeggutor, env->envp);
}
