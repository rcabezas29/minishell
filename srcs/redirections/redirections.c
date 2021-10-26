/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/10/26 13:41:12 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	ft_indirection(t_cmd_info *cmd_info)
// {

// }

// void	ft_redirection(t_cmd_info *cmd_info)
// {

// }

// void	ft_append(t_cmd_info *cmd_info)
// {

// }

void	ft_heredoc(t_cmd_info *cmd_info, char *file)
{
	t_list	*aux;
	char	*aux2;
	char	*tmp;
	int		fd;

	aux = cmd_info->command_list;
	fd = 0;
	if (cmd_info->line)
		free(cmd_info->line);
	cmd_info->line = ft_strdup("");
	while (1)
	{
		tmp = readline("> ");
		if (tmp[0] != '\0')
		{
			if (ft_strncmp(file, tmp, ft_strlen(tmp)))
			{
				aux2 = ft_strjoin(tmp, "\n");
				free(tmp);
				tmp = NULL;
				tmp = ft_strdup(cmd_info->line);
				free(cmd_info->line);
				cmd_info->line = ft_strjoin(tmp, aux2);
				free (aux2);
				aux2 = NULL;
				free (tmp);
				tmp = NULL;
			}
			else
			{
				free(tmp);
				break ;
			}
		}
	}
}

void	ft_manageredirections(t_cmd_info *cmd_info)
{
	t_list	*tmp;

	tmp = cmd_info->command_list;
	while (tmp && ((t_node *)tmp->content)->types != 1)
	{
		// if (((t_node *)tmp->content)->types == 2)
		// 	ft_indirection(cmd_info);
		// else if (((t_node *)tmp->content)->types == 3)
		// 	ft_redirection(cmd_info);
		if (((t_node *)tmp->content)->types == 4)
		{
			tmp = tmp->next;
			ft_heredoc(cmd_info, ((t_node *)tmp->content)->prompts);
			break ;
		}
		// else if (((t_node *)tmp->content)->types == 5)
		// 	ft_append(cmd_info);
		tmp = tmp->next;
	}
}
