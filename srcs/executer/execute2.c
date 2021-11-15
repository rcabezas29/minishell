/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:19:36 by fballest          #+#    #+#             */
/*   Updated: 2021/11/15 15:19:32 by rcabezas         ###   ########.fr       */
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

int	execute_builtins(t_exe exe, t_env *env)
{
	int		ret;

	if (!ft_strcmp(exe.cmd, "echo"))
		ret = execute_echo(exe);
	if (!ft_strcmp(exe.cmd, "cd"))
		ret = execute_cd(exe, env);
	else if (!ft_strcmp(exe.cmd, "pwd"))
		ret = execute_pwd();
	else if (!ft_strcmp(exe.cmd, "env"))
		ret = execute_env(exe, env);
	else if (!ft_strcmp(exe.cmd, "export"))
		ret = execute_export(exe, env);
	else if (!ft_strcmp(exe.cmd, "unset"))
		ret = execute_unset(exe, env);
	else if (!ft_strcmp(exe.cmd, "exit"))
		ret = execute_exit(exe);
	return (ret);
}

void	analyze_prompt(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;

	aux = cmd_info->command_list;
	if (((t_node *)aux->content)->types == 1)
		perror("syntax error near unexpected token `|'\n");
	while (aux)
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
