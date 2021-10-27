/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:50:24 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/27 12:24:05 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sig_int(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	return ;
}

static void	sig_quit(int sig)
{
	if (sig == 2)
	{
		(void)sig;
		rl_replace_line ("\033[0;32mminishell - \033[0;0m", 0);
	}
	else if (sig == 3)
	{
		(void)sig;
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	sig_init(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}
