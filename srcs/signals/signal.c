/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:50:24 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/26 13:41:11 by fballest         ###   ########.fr       */
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
