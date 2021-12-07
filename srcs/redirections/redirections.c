/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/12/06 22:35:08 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_append(char *filename, t_cmd_info *cmd_info)
{
	int		fd;

	fd = 0;
	if (!access(filename, W_OK))
		fd = open(filename, O_RDWR | O_APPEND);
	else
		fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		cmd_info->return_code = errno;
		write(2, "minishell: ", 12);
		write(2, filename, 1);
		write(2, ": syntax error near unexpected token\n", 37);
		return (cmd_info->return_code);
	}
	return (fd);
}

int	ft_indirection(char *filename, t_cmd_info *cmd_info)
{
	int		fd;

	fd = 0;
	if (!access(filename, R_OK))
		fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, filename, ft_strlen(filename));
		write(2, "No such file or directory", 26);
		cmd_info->return_code = -1;
	}
	return (fd);
}

int	ft_redirection(char *filename, t_cmd_info *cmd_info)
{
	int		fd;

	fd = 0;
	if (opendir (filename))
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, " is a directory/n", 17);
		closedir ((DIR *)filename);
		return (cmd_info->return_code = -126);
	}
	if (!access(filename, R_OK))
		unlink(filename);
	fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		write(2, "minishel: syntax error near unexpected token ", 45);
		write(2, filename, ft_strlen(filename));
		write(2, "\n", 1);
		cmd_info->return_code = (-1);
		return (cmd_info->return_code);
	}
	return (fd);
}

void	ft_manageredirections_b(t_cmd_info *cmd_info, t_list *tmp)
{
	if (((t_node *)tmp->content)->types == 2)
	{
		tmp = tmp->next;
		((t_node *)tmp->content)->fd_in
			= ft_indirection(((t_node *)tmp->content)->prompts, cmd_info);
	}
	else if (((t_node *)tmp->content)->types == 3)
	{
		tmp = tmp->next;
		((t_node *)tmp->content)->fd_out
			= ft_redirection(((t_node *)tmp->content)->prompts, cmd_info);
	}
	else if (((t_node *)tmp->content)->types == 5)
	{
		tmp = tmp->next;
		((t_node *)tmp->content)->fd_out
			= ft_append(((t_node *)tmp->content)->prompts, cmd_info);
	}
}

void	ft_manageredirections(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*tmp;

	tmp = cmd_info->command_list;
	while (tmp)
	{
		ft_manageredirections_b(cmd_info, tmp);
		if (((t_node *)tmp->content)->types == 4)
		{
			tmp = tmp->next;
			if (!ft_strlen(((t_node *)tmp->content)->prompts))
			{
				write (2, "minishell: Non-existing enviroment variable\n", 44);
				cmd_info->return_code = 1;
				continue ;
			}
			((t_node *)tmp->content)->fd_in
				= ft_heredoc((char *)((t_node *)tmp->content)->prompts,
					cmd_info, env, ((t_node *)tmp->content)->comillas);
		}
		tmp = tmp->next;
	}
}
