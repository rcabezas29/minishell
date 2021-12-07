/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:40:35 by fballest          #+#    #+#             */
/*   Updated: 2021/12/06 22:47:59 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expand_conditions(char *prompt, char *tmp, t_pparse *pp)
{
	int		z;

	z = 0;
	if ((prompt[pp->i] == '>' && prompt[pp->i + 1] == '>'
		&& prompt[pp->i + 2] == '>') || (prompt[pp->i] == '<'
		&& prompt[pp->i + 1] == '<' && prompt[pp->i + 2] == '<')
		|| (prompt[pp->i] == '>' && prompt[pp->i + 1] == '<')
		|| (prompt[pp->i] == '<' && prompt[pp->i + 1] == '>'))
		z = 666;
	else if (prompt[pp->i] == '>' && prompt[pp->i + 1] == '>')
		z = 2;
	else if (prompt[pp->i] == '<' && prompt[pp->i + 1] == '<')
		z = 2;
	else if (prompt[pp->i] == '>')
		z = 1;
	else if (prompt[pp->i] == '<')
		z = 1;
	else
		tmp[pp->j++] = prompt[pp->i++];
	return (z);
}
