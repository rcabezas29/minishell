/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:34:56 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/21 18:47:09 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_after_know_flag(int n, t_list *tmp)
{
	if (n == 1)
	{
		while (tmp && ((t_node *)tmp->content)->types == 0)
		{
			printf("%s", ((t_node *)tmp->content)->prompts);
			if (tmp->next)
				printf(" ");
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp && ((t_node *)tmp->content)->types == 0)
		{
			printf("%s ", ((t_node *)tmp->content)->prompts);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

int	flag_to_one(t_list **tmp)
{
	*tmp = (*tmp)->next;
	return (1);
}

void	execute_echo(t_cmd_info *cmd_info)
{
	t_list	*tmp;
	int		i;
	int		n;

	if (!cmd_info->command_list->next)
	{
		printf("\n");
		return ;
	}
	tmp = cmd_info->command_list->next;
	n = 0;
	while (tmp && !ft_strncmp(((t_node *)tmp->content)->prompts, "-n", 2))
	{
		i = 1;
		while (((t_node *)tmp->content)->prompts[i + 1]
			&& ((t_node *)tmp->content)->prompts[i + 1] == 'n')
			i++;
		if (((t_node *)tmp->content)->prompts[i + 1])
			break ;
		else
			n = flag_to_one(&tmp);
	}
	print_after_know_flag(n, tmp);
}
