/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:55:10 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/13 21:38:34 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

void	manage_fds(t_exe exe, int *fd_stdin, int *fd_stdout)
{
	*fd_stdin = dup(STDIN_FILENO);
	*fd_stdout = dup(STDOUT_FILENO);
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
}

char	**assign_arguments_with_cmd(t_exe exe)
{
	char	**exeggutor;
	int		i;

	exeggutor = ft_calloc(sizeof(char *), (ft_matrixlen(exe.args) + 2));
	exeggutor[0] = ft_strdup(exe.cmd);
	i = 0;
	while (i < ft_matrixlen(exe.args))
	{
		i++;
		exeggutor[i] = ft_strdup(exe.args[i - 1]);
	}
	return (exeggutor);
}

int	check_builtin(char *cmd)
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
	int				saved_stdin;
	int				saved_stdout;

	if (!cmd_info->exe[0].cmd)
		return (0);
	manage_fds(cmd_info->exe[0], &saved_stdin, &saved_stdout);
	if (check_builtin(cmd_info->exe[0].cmd))
	{
		execute_builtins(cmd_info, env);
		restore_fds(saved_stdin, saved_stdout);
		return (cmd_info->return_code);
	}
	else
	{
		j = 0;
		path = cmd_path(env, cmd_info->exe[0].cmd);
		exeggutor = assign_arguments_with_cmd(cmd_info->exe[0]);
		pid = fork();
		if (pid == 0)
		{
			son_signal();
			cmd_info->return_code = execve(path, exeggutor, env->envp);
			ft_freematrix(exeggutor);
			free(path);
			exit(cmd_info->return_code);
		}
		else
		{
			waitpid(pid, &j, 0);
			free(path);
			path = NULL;
			ft_freematrix(exeggutor);
		}
		restore_fds(saved_stdin, saved_stdout);
		return (j % 255);
	}
}
