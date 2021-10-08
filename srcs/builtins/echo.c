/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:34:56 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/08 10:03:25 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_echo(t_cmd_info *cmd_info)
{
	t_list	*tmp;

	tmp = cmd_info->command_list->next;
	if (tmp->next && !ft_strcmp(((t_node *)tmp->content)->prompts, "-n"))
	{
		tmp = tmp->next;
		while (tmp && ((t_node *)tmp->content)->types == 0)
		{
			printf("%s", ((t_node *)tmp->content)->prompts);
			tmp = tmp->next;
		}
		return ;
	}
	while (tmp && ((t_node *)tmp->content)->types == 0)
	{
		printf("%s", ((t_node *)tmp->content)->prompts);
		tmp = tmp->next;
	}
	printf("\n");
}
