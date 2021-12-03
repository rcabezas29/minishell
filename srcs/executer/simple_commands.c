/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:55:10 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/03 17:10:34 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

int	execute_execve_on_simple_commands(t_cmd_info *cmd_info, t_env *env,
	int saved_stdin, int saved_stdout)
{
	char	*path;
	int		pid;
	int		j;
	char	**exeggutor;

	j = 0;
	child_signal();
	pid = fork();
	if (pid == 0)
	{
		path = cmd_path(env, cmd_info->exe[0].cmd);
		exeggutor = assign_arguments_with_cmd(cmd_info->exe[0]);
		execve(path, exeggutor, env->envp);
	}
	else
	{
		restore_fds(saved_stdin, saved_stdout);
		waitpid(pid, &j, 0);
		cancel_signals();
	}
	return (j % 256);
}

int	execute_simple_commands(t_cmd_info *cmd_info, t_env *env)
{
	int				saved_stdin;
	int				saved_stdout;

	if (cmd_info->exe[0].fd_in < 0 || cmd_info->exe[0].fd_out < 0)
		return (1);
	if (!cmd_info->exe[0].cmd)
		return (0);
	manage_fds(cmd_info->exe[0], &saved_stdin, &saved_stdout);
	if (check_builtin(cmd_info->exe[0].cmd))
	{
		cmd_info->return_code = execute_builtins(cmd_info->exe[0], env);
		restore_fds(saved_stdin, saved_stdout);
		return (cmd_info->return_code);
	}
	else
		return (execute_execve_on_simple_commands(cmd_info, env,
				saved_stdin, saved_stdout));
}
