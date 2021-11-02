/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/11/02 13:02:42 by fballest         ###   ########.fr       */
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
// static void	ft_heredoc_buc(char *file, int fd)
// {
// 	char	*tmp;

// 	while (1)
// 	{
// 		tmp = readline("> ");
// 		if (tmp[0] != '\0')
// 		{
// 			//INCLUIR FUNCION PARA EXPANSION VARIABLES DE ENTORNO
// 			if (!ft_strncmp(file, tmp, ft_strlen(file) + 1))
// 			{
// 				free(tmp);
// 				break ;
// 			}
// 			else
// 				write(fd, tmp, ft_strlen(tmp));
// 			free (tmp);
// 			write (fd, "\n", 1);
// 		}
// 	}
// }

// void	ft_heredoc(t_cmd_info *cmd_info, char *file)
// {
// 	char	*tmp;
// 	char	pwd[FILENAME_MAX];
// 	int		fd;

// 	if (cmd_info->file)
// 	{
// 		unlink(cmd_info->file);
// 		free(cmd_info->file);
// 	}
// 	getcwd(pwd, FILENAME_MAX);
// 	tmp = ft_strjoin(pwd, "/");
// 	cmd_info->file = ft_strjoin(tmp, file);
// 	free (tmp);
// 	fd = open(cmd_info->file, O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
// 	if (fd < 0)
// 		return ;
// 	ft_heredoc_buc(file, fd);
// 	close (fd);
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

int	ft_indirection(char *filename, t_cmd_info *cmd_info)
{
	int		fd;

	fd = 0;
	if (!access(filename, R_OK))
		fd = open(filename, S_IRUSR);
	if (fd < 0)
	{
		printf("%s:%s\n", filename, "No such file or directory");
		cmd_info->return_code = -1;
	}
	return (fd);
}

int	ft_redirection(char *filename, t_cmd_info *cmd_info)
{
	int		fd;

	fd = 0;
	fd = open(filename, O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
	if (fd < 0)
	{
		printf("minishel: %s: %c\n", "syntax error near unexpected token",
			filename[0]);
		cmd_info->return_code = (-1);
		return (cmd_info->return_code);
	}
	else if (fd == 0)
	{
		printf("minishel: %s: %s\n", filename, "event nor found");
		cmd_info->return_code = 0;
		return (cmd_info->return_code);
	}
	return (fd);
}

void	ft_manageredirections(t_cmd_info *cmd_info)
{
	t_list	*tmp;

	tmp = cmd_info->command_list;
	while (tmp && ((t_node *)tmp->content)->types != 1)
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
		else if (((t_node *)tmp->content)->types == 4)
		{
			tmp = tmp->next;
			ft_heredoc(cmd_info, ((t_node *)tmp->content)->prompts);
			break ;
		}
		else if (((t_node *)tmp->content)->types == 5)
		{
			tmp = tmp->next;
			ft_append(cmd_info, ((t_node *)tmp->content)->prompts);
			break ;
		}
		tmp = tmp->next;
	}
}
