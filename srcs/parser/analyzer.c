/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:32:58 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/24 17:33:14 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	analyze_prompt(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;

	aux = cmd_info->command_list;
	if (((t_node *)aux->content)->types == 1)
		write(2, "syntax error near unexpected token `|'\n", 40);
	while (aux)
	{
		if (((t_node *)aux->content)->types > 1
			&& ((t_node *)aux->content)->types < 6)
		{
			aux = aux->next;
			((t_node *)aux->content)->types = FILE_NAME;
			ft_manageredirections(cmd_info, env);
		}
		aux = aux->next;
	}
}
