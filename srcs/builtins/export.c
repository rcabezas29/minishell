/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:39:38 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/13 20:56:42 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**order_envs(char **envs)
{
	char	**ordered;

	ordered = malloc(sizeof(envs));
	
}

void	print_envs_export(char	**envs)
{
	char	**ordered;

	ordered = order_envs(envs);
}

void	execute_export(t_cmd_info *cmd_info, t_env *env)
{
	if (count_arguments(cmd_info->command_list) == 1)
	{
		print_envs_export(env->envp);
		return ;
	}
}