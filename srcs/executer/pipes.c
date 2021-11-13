/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:20:01 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/13 12:58:52 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	**create_pipes(int no_pipes)
{
	int	fd[no_pipes][2];
	int	i;

	i  = 0;
	while (i < no_pipes)
	{
		pipe(fd[i]);
		i++;
	}
	return(fd);
}

int	waiting_room(void)
{
	int	j;
	
	j = 0;
	waitpid(-1, &j, 0);
	return (j);
}

int	execute_pipes(t_cmd_info *cmd_info, t_env *env)
{
	int		**fd;
	int		i;
	int		j;
	pid_t	pid;
	
	fd = create_pipes(cmd_info->no_pipes);
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
}
