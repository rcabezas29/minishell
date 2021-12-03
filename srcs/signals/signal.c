/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:50:24 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/03 09:11:26 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_line_buffer[0] = '\0';
	rl_point = 0;
	rl_end = 0;
	rl_redisplay();
	return ;
}

void	sig_quit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	sig_init(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}

void	cancel_signals(void)
{
	signal(SIGINT, not_sig_int);
	signal(SIGQUIT, not_sig_quit);
}
