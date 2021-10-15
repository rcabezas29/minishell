/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:13:53 by fballest          #+#    #+#             */
/*   Updated: 2021/10/15 12:06:40 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_cleanmemory(t_cmd_info *cmd_info, t_env *env)
{
	ft_lstclear(&cmd_info->command_list, del);
	ft_freearray(env->paths);
	free(env);
	free(cmd_info->command_list);
	free(cmd_info);
	clear_history();
	atexit(leaks);
}

void	execute_exit(t_cmd_info *cmd_info, t_env *env)
{
	ft_cleanmemory(cmd_info, env);
	exit (0);
}
