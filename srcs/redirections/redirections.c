/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/11/22 15:57:32 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*fill_env(char *dollar, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (ft_strcmp("", dollar))
	{
		while (env->envp[i])
		{
			if (!ft_strncmp(env->envp[i], dollar, ft_strlen(dollar)))
				tmp = ft_strdup(ft_strchr2(env->envp[i], '='));
			i++;
		}
	}
	if (!tmp)
		tmp = ft_strjoin("$", dollar);
	free (dollar);
	return (tmp);
}

static char	*heredoc_expander(char *tmp, t_env *env)
{
	int		i;
	int		j;
	int		z;
	char	*str1;
	char	*str2;

	str1 = ft_strdup("");
	str2 = ft_strdup("");
	i = 0;
	j = 0;
	while (tmp[i])
		if (tmp[i++] == '$')
			j++;
	while (j > 0)
	{
		i = 0;
		while (j > 0 && tmp[i] && tmp[i] != '$')
		{
			str1 = ft_realloc(str1, (ft_strlen(str1) + 2));
			str1[i] = tmp[i];
			i++;
			str1[i++] = '\0';
		}
		z = 0;
		if (tmp[i] == '$' && (tmp[i + 1] != '\''
				&& tmp[i + 1] != '\"' && tmp[i + 1] != ' '))
		{
			i++;
			while (tmp[i] && (tmp[i] != '\'' && tmp[i] != '\"' && tmp[i] != ' '))
			{
				str2 = ft_realloc(str2, (ft_strlen(str2) + 2));
				str2[z++] = tmp[i++];
				str2[z] = '\0';
			}
			str2 = fill_env(str2, env);
		}
		else
		{
			while (tmp[i])
				if ((tmp[i + 1] = '\'' && tmp[i + 1] != '\"' && tmp[i + 1] != ' '))
					str2[z++] = tmp[i++];
 		}
		z = 0;
		while (str2[z] != '\0')
			z++;
		while (tmp[i])
		{
			str2 = ft_realloc(str2, (ft_strlen(str2) + 2));
			str2[z++] = tmp[i++];
			str2[z] = '\0';
		}
		free (tmp);
		tmp = ft_strjoin(str1, str2);
		j--;
	}
	free (str1);
	free (str2);
	return (tmp);
}

void	ft_heredoc_bucle(char *file, t_env *env, int comillas, int fd)
{
	char	*tmp;
	char	*aux;

	while (1)
	{
		tmp = readline("> ");
		if (tmp[0] != '\0')
		{
			if (!ft_strncmp(file, tmp, ft_strlen(file) + 1))
				break ;
			else if (ft_strncmp(file, tmp, ft_strlen(file) + 1))
			{
				if (comillas == 0)
					aux = heredoc_expander(tmp, env);
				else
					aux = ft_strdup(tmp);
				write (1, aux, ft_strlen(aux));
				write (1, "\n", 1);
				free (aux);
			}
		}
		// free (tmp);
	}
	comillas = fd;
}

int	ft_heredoc(char *file, t_cmd_info *cmd_info, t_env *env, int comillas)
{
	char	*filename;
	int		fd;

	filename = "/private/tmp/hd_ms2021.txt";
	if (!access(filename, W_OK))
		unlink(filename);
	fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		cmd_info->return_code = errno;
		perror("minishell: ");
		return (0);
	}
	else
		ft_heredoc_bucle(file, env, comillas, fd);
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
				= ft_heredoc(((t_node *)tmp->content)->prompts,
					cmd_info, env, ((t_node *)tmp->content)->comillas);
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
