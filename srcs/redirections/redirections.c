/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/10/29 10:31:48 by fballest         ###   ########.fr       */
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
static void	ft_heredoc_buc(char *file, int fd)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (tmp[0] != '\0')
		{
			//INCLUIR FUNCION PARA EXPANSION VARIABLES DE ENTORNO
			if (!ft_strncmp(file, tmp, ft_strlen(file) + 1))
			{
				free(tmp);
				break ;
			}
			else
				write(fd, tmp, ft_strlen(tmp));
			free (tmp);
			write (fd, "\n", 1);
		}
	}
}

void	ft_heredoc(t_cmd_info *cmd_info, char *file)
{
	char	*tmp;
	char	pwd[FILENAME_MAX];
	int		fd;

	if (cmd_info->file)
	{
		unlink(cmd_info->file);
		free(cmd_info->file);
	}
	getcwd(pwd, FILENAME_MAX);
	tmp = ft_strjoin(pwd, "/");
	cmd_info->file = ft_strjoin(tmp, file);
	free (tmp);
	fd = open(cmd_info->file, O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
	if (fd < 0)
		return ;
	ft_heredoc_buc(file, fd);
	close (fd);
}

void	ft_indirection(t_cmd_info *cmd_info, char *file)
{
	t_list	*aux;
	int		fd;

	aux = cmd_info->command_list;
	if (!access(file, R_OK))
		fd = open(file, S_IRUSR);
	// while (((t_node *)aux->content)->prompts
	// 	&& ft_strncmp("<", ((t_node *)aux->content)->prompts))
	// {
	// 	if (ft_strncmp("<", ft_strncmp("<", ((t_node *)aux->content)->prompts)))
	// 		aux = aux->next;
	// 	else
	// 	{
	// 		aux = aux->next;
	// 		if (((t_node *)aux->content)->comillas == 1)
	// 			check_argtoexpand()
	// 	}

	// }
}

void	ft_manageredirections(t_cmd_info *cmd_info)
{
	t_list	*tmp;

	tmp = cmd_info->command_list;
	while (tmp && ((t_node *)tmp->content)->types != 1)
	{
		if (((t_node *)tmp->content)->types == 2)
			ft_indirection(cmd_info, ((t_node *)tmp->content)->prompts);
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
