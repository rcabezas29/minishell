/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:19:36 by fballest          #+#    #+#             */
/*   Updated: 2021/11/13 21:36:34 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*cmd_path(t_env *env, char *cmd)
{
	char	*path;
	char	*tmp;
	int		check_path;

	check_path = 0;
	tmp = NULL;
	path = cmd_path2(cmd, tmp, check_path, env);
	if (!path)
	{
		tmp = ft_strjoin(cmd, ": command not found\n");
		ft_putstr(tmp);
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	return (path);
}

void	execute_builtins(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;

	aux = cmd_info->command_list;
	if (!ft_strcmp(((t_node *)aux->content)->prompts, "echo"))
		execute_echo(cmd_info);
	if (!ft_strcmp(((t_node *)aux->content)->prompts, "cd"))
		execute_cd(cmd_info, env);
	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "pwd"))
		execute_pwd();
	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "env"))
		execute_env(cmd_info, env);
	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "export"))
		execute_export(cmd_info, env);
	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "unset"))
		execute_unset(cmd_info, env);
	else if (!ft_strcmp(((t_node *)aux->content)->prompts, "exit"))
		execute_exit(cmd_info, env);
}

void	analyze_prompt(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;

	aux = cmd_info->command_list;
	if (((t_node *)aux->content)->types == 1)
		perror("syntax error near unexpected token `|'\n");
	if (((t_node *)aux->content)->types > 1
		&& ((t_node *)aux->content)->types < 6)
	{
		aux = aux->next;
		((t_node *)aux->content)->types = FILE_NAME;
		ft_manageredirections(cmd_info, env);
		if (aux->next)
			aux = aux->next;
	}
	while (aux && ((t_node *)aux->content)->types != 1)
	{
		if (((t_node *)aux->content)->types > 1
			&& ((t_node *)aux->content)->types < 6)
		{
			aux = aux->next;
			((t_node *)aux->content)->types = FILE_NAME;
			ft_manageredirections(cmd_info, env);
		}
		aux = aux->next;
	}
}
