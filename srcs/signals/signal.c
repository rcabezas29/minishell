/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:50:24 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/02 09:49:42 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static void	sig_int(int sig)
// {
// 	(void)sig;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_redisplay();
// 	return ;
// }

// static void	sig_quit(int sig)
// {
// 	(void)sig;
// 	rl_on_new_line();
// 	rl_redisplay();
// 	return ;
// }

// void	sig_init(void)
// {
// 	signal(SIGINT, sig_int);
// 	signal(SIGQUIT, sig_quit);
// }

static void	sig_int(int sig)
{
	(void)sig;
	rl_redisplay();
	return ;
}

static void	sig_quit(int sig)
{
	(void)sig;
	printf("\n\r");
	rl_redisplay();
	rl_replace_line ("\033[0;32mminishell - \033[0;0m", 0);
	return ;
}

void	son_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_init(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}
