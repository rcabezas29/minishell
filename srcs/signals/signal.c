/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:50:24 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/23 11:03:58 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	not_sig_quit(int sig)
{
	(void)sig;
	return ;
}

static void	not_sig_int(int sig)
{
	(void)sig;
	return ;
}

static void	sig_int_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	return ;
}

static void	sig_quit_child(int sig)
{
	(void)sig;
	write(1, "QUIT: 3\n", 8);
	return ;
}

static void	sig_int(int sig)
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

static void	sig_quit(int sig)
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

void	son_signal(void)
{
	signal(SIGINT, sig_int_child);
	signal(SIGQUIT, sig_quit_child);
}

void	cancel_signals(void)
{
	signal(SIGINT, not_sig_int);
	signal(SIGQUIT, not_sig_quit);
}
