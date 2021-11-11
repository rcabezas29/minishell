/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:27:54 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/11 21:11:04 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	assign_arguments_from_list(t_list *tmp, t_exe *exe, int n)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (count_arguments(tmp) + 1));
	i = 0;
	while (tmp && ((t_node *)tmp->content)->types == ARGUMENT)
	{
		args[i] = ft_strdup(((t_node *)tmp->content)->prompts);
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	exe[n].args = ft_matrixdup(args);
	ft_freematrix(args);
}

static void	assign_fd_from_list(t_list *tmp, t_exe *exe, int n)
{
	if (((t_node *)tmp->content)->fd_in)
		exe[n].fd_in = ((t_node *)tmp->content)->fd_in;
	if (((t_node *)tmp->content)->fd_out)
		exe[n].fd_out = ((t_node *)tmp->content)->fd_out;
}

static void	fill_exe(t_cmd_info *cmd_info)
{
	t_list	*tmp;
	int		i;
	int		arg;
	int		j;

	tmp = cmd_info->command_list;
	i = 0;
	while (tmp)
	{
		arg = 0;
		while (tmp && ((t_node *)tmp->content)->types != PIPE)
		{
			if (((t_node *)tmp->content)->types == ARGUMENT && arg == 0)
			{
				cmd_info->exe[i].cmd = ft_strdup(((t_node *)tmp->content)->prompts);
				arg = 1;
			}
			else if (((t_node *)tmp->content)->types == ARGUMENT && arg == 1)
			{
				assign_arguments_from_list(tmp, cmd_info->exe, i);
				j = 0;
				while (j < count_arguments(tmp) - 1)
					tmp = tmp->next;
			}
			else if (((t_node *)tmp->content)->types == FILE_NAME)
				assign_fd_from_list(tmp, cmd_info->exe, i);
			tmp = tmp->next;
		}
		i++;
		if (tmp)
			tmp = tmp->next;
	}
}

static void	downcase_cmds(t_cmd_info *cmd_info)
{
	int	i;

	i = 0;
	while (i <= cmd_info->no_pipes)
		ft_strdowncase(cmd_info->exe[i++].cmd);
}

void	parser(t_cmd_info *cmd_info)
{
	int		i;

	i = 0;
	cmd_info->exe = ft_calloc(sizeof(t_exe), cmd_info->no_pipes + 2);
	fill_exe(cmd_info);
	downcase_cmds(cmd_info);
}
