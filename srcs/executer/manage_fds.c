/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:15:45 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/24 13:16:52 by rcabezas         ###   ########.fr       */
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
