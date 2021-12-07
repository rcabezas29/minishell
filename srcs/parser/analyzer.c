/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:32:58 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/07 08:35:16 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	analyze_prompt(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;

	aux = cmd_info->command_list;
	if (aux && ((t_node *)aux->content)->types == 1)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		cmd_info->return_code = 258;
	}
	while (aux)
	{
		if (((t_node *)aux->content)->types > 1
			&& ((t_node *)aux->content)->types < 6)
		{
			if (aux->next)
				aux = aux->next;
			else
			{
				ft_putstr_fd(
					"minishell: syntax error near unexpected token\n", 2);
				cmd_info->return_code = 258;
				break ;
			}
			((t_node *)aux->content)->types = FILE_NAME;
			ft_manageredirections(cmd_info, env);
		}
		aux = aux->next;
	}
}
