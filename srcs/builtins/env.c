/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:38:39 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/19 11:34:36 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_env(t_cmd_info *cmd_info, t_env *env)
{
	int		i;
	t_list	*tmp;

	tmp = cmd_info->command_list;
	if (count_arguments(tmp) > 1)
	{
		printf("%s: No such file or directory\n", ((t_node *)tmp->next->content)->prompts);
		cmd_info->return_code = 127;
	}
	else
	{
		i = 0;
		while (env->envp[i])
		{
			if (ft_strchr(env->envp[i], '='))
				printf("%s\n", env->envp[i]);
			i++;
		}
	}
}
