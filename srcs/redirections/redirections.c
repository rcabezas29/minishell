/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/11/19 09:39:43 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*fill_env(char *dollar, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], dollar, ft_strlen(dollar)))
			tmp = ft_strchr2(env->envp[i], '=');
		i++;
	}
	free (dollar);
	if (!tmp)
		return (NULL);
	return (tmp);
}


int	ft_heredoc_bucle(char *file, char *filename, t_cmd_info *cmd_info, int fd)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (tmp[0] != '\0')
		{
			if (ft_strncmp(file, tmp, ft_strlen(tmp)))
			{
			
			}
			else if (!ft_strncmp(file, tmp, ft_strlen(file) + 1))
			{
			
			}
			else
				return(fd);
		}
	}
}

int	ft_heredoc(char *file, t_cmd_info *cmd_info, t_env *env)
{
	char	*filename;
	int		fd;

	filename = "/private/tmp/hd_ms2021.txt";
	if (!access(filename, W_OK))
		unlink(filename);
	fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		cmd_info->return_code = (15);
		return (0);
	}
	fd = ft_heredoc_bucle(file, filename, cmd_info, fd);
	return (fd);
}

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
		write(2, "minishell: ", 12);
		write(2, &filename[0], 1);
		write(2, ": syntax error near unexpected token", 35);
		cmd_info->return_code = errno;
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
	if (!access(filename, R_OK))
		unlink(filename);
	fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		write(2, "minishel: syntax error near unexpected token", 45);
		write(2, &filename[0], 1);
		cmd_info->return_code = (-1);
		return (cmd_info->return_code);
	}
	return (fd);
}

void	ft_manageredirections(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*tmp;

	tmp = cmd_info->command_list;
	while (tmp)
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
			((t_node *)tmp->content)->fd_in
				= ft_heredoc(((t_node *)tmp->content)->prompts, cmd_info, env);
		}
		else if (((t_node *)tmp->content)->types == 5)
		{
			tmp = tmp->next;
			((t_node *)tmp->content)->fd_out
				= ft_append(((t_node *)tmp->content)->prompts, cmd_info);
		}
		tmp = tmp->next;
	}
}
