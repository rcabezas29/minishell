/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/12/09 12:00:08 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*extract_root(char *filename)
{
	int		i;
	int		pos;
	char	*tmp;

	tmp = ft_strdup(filename);
	pos = 0;
	i = 0;
	while (filename[i])
	{
		if (filename[i++] == '/')
			pos = i;
	}
	tmp[pos] = '\0';
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = ft_strdup(filename);
	}
	return (tmp);
}

int	ft_append(char *filename, t_cmd_info *cmd_info)
{
	int		fd;
	char 	*tmp;
	DIR		*dir;

	fd = 0;
	tmp = extract_root(filename);
	dir = opendir(tmp);
	if (!dir)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, " : No such file or directory\n", 30);
		free(tmp);
		return (cmd_info->return_code = -11);
	}
	closedir(dir);
	if (!access(filename, W_OK))
		fd = open(filename, O_RDWR | O_APPEND);
	else
		fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		cmd_info->return_code = errno;
		write(2, "minishell: ", 12);
		write(2, filename, ft_strlen(filename));
		write(2, ": syntax error near unexpected token\n", 38);
		return (cmd_info->return_code);
	}
	return (fd);
}

int	ft_indirection(char *filename, t_cmd_info *cmd_info)
{
	int		fd;
	DIR		*dir;
	char	*tmp;

	fd = 0;
	tmp = extract_root(filename);
	dir = opendir(tmp);
	if (!dir)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, " : No such file or directory\n", 30);
		free (tmp);
		return (cmd_info->return_code = -126);
	}
	closedir(dir);
	if (access(filename, R_OK))
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, " : No such file or directory\n", 30);
		free (tmp);
		return (cmd_info->return_code = -1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, " : No such file or directory\n", 30);
		free (tmp);
		return (cmd_info->return_code = -1);
	}
	free(tmp);
	return (fd);
}

int	ft_redirection(char *filename, t_cmd_info *cmd_info)
{
	int		fd;
	char	*tmp;
	DIR		*dir;

	fd = 0;
	tmp = extract_root(filename);
	dir = opendir(tmp);
	if (!dir)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, " : No such file or directory\n", 30);
		free(tmp);
		return (cmd_info->return_code = -11);
	}
	closedir(dir);
	if (!access(filename, R_OK))
		unlink(filename);
	fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		write(2, "minishel: syntax error near unexpected token ", 45);
		write(2, filename, ft_strlen(filename));
		write(2, "\n", 1);
		free(tmp);
		return (cmd_info->return_code = -1);
	}
	return (fd);
}

void	ft_manageredirections(t_cmd_info *cmd_info, t_env *env, t_node *node,
		t_type type)
{
	if (type == HERE_DOC)
	{
		if (!ft_strlen(node->prompts))
		{
			write (2, "minishell: Non-existing enviroment variable\n", 44);
			cmd_info->return_code = 1;
			return ;
		}
		node->fd_in = ft_heredoc(node->prompts, cmd_info, env, node->comillas);
	}
	else if (type == INDIRECTION)
		node->fd_in = ft_indirection(node->prompts, cmd_info);
	else if (type == REDIRECTION)
		node->fd_out = ft_redirection(node->prompts, cmd_info);
	else if (type == APPEND)
		node->fd_out = ft_append(node->prompts, cmd_info);
}
