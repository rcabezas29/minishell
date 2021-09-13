/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:21:24 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/13 15:10:58 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_commands(char *command, t_env *env)
{
	if (!ft_strncmp(command, "echo", 4))
		echo(command);
	else if (!ft_strncmp(command, "cd", 2))
		cd(command);
	else if (!ft_strncmp(command, "pwd", 3))
		pwd(command);
	else if (!ft_strncmp(command, "export", 6))
		export(command);
	else if (!ft_strncmp(command, "unset", 5))
		unset(command);
	else if (!ft_strncmp(command, "env", 3))
		env_function(command);
	else
		path_command(command, env);
}

void	path_command(char *command, t_env *env)
{
	char	*path;
	char	*tmp;
	int		i;
	int		check_path;

	path = NULL;
	i = 0;
	while (env->paths[i])
	{
		tmp = ft_strjoin(ft_strjoin(env->paths[i], "/"), ft_split(command, ' ')[0]);
		check_path = open(tmp, O_RDONLY);
		if (check_path < 0)
			i++;
		else
		{
			path = tmp;
			break ;
		}
	}
	if (!path)
		ft_putstr_fd(ft_strjoin(command, ": command not found"), 1);
	execute(path, command, env);
}

void	execute(char *path, char *command, t_env *env)
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
		execve(path, ft_split(command, ' '), env->envp);
}
