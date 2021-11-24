/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_sigs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:46:22 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/24 12:48:03 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	not_sig_quit(int sig)
{
	(void)sig;
	return ;
}

void	not_sig_int(int sig)
{
	(void)sig;
	return ;
}

void	sig_int_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	return ;
}

void	sig_quit_child(int sig)
{
	(void)sig;
	write(1, "QUIT: 3\n", 8);
	return ;
}

void	child_signal(void)
{
	signal(SIGINT, sig_int_child);
	signal(SIGQUIT, sig_quit_child);
}
