/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:27:12 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/13 12:39:12 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_first_pipe(t_exe exe, t_env *env, int fd[])
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd[WRITE_END], STDOUT_FILENO);
	
	
}

void	execute_last_pipe(t_exe exe, t_env *env, int fd[])
{

}

void	execute_between_pipes(t_exe exe, t_env *env, int read_fd[], int write_fd[])
{
	
}
