/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/10/18 12:10:25 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		ft_redirections(t_cmd_info *cmd_info)
{
	t_list	*tmp;

	tmp = cmd_info->command_list;
	while (((t_node *)tmp->content)->types != 1)
	{
		if (((t_node *)tmp->content)->types == 2)
		{
			printf("HOLA 2");
		}
		else if (((t_node *)tmp->content)->types == 3)
		{
			printf("HOLA 3");
		}
		else if (((t_node *)tmp->content)->types == 4)
		{
			printf("HOLA 4");
		}
		else if (((t_node *)tmp->content)->types == 5)
		{
			printf("HOLA 5");
		}
		tmp = tmp->next;
	}
}
