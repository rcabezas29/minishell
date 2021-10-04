/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:36:49 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/28 10:36:51 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	manage_points(char *arg, char *pwd)
{
	
}

void	execute_cd(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;
	int		nargs;
	char	*path;

	aux = cmd_info->command_list->next;
	nargs = count_arguments(aux);
	if (nargs > 2)
	{
		perror("string not in pwd");
		return ;
	}
	else if (nargs == 1)
	{
		env->pwd = ft_strdup(env->home);
		return ;
	}
	else
	{
		if (((t_node *)aux->content)->prompts[0] == '/')
		{
			path = ft_strdup(((t_node *)aux->content)->prompts);
			if (open(path, O_RDONLY) < 0)
			{
				perror("no such file or directory");
				return ;
			}
		}
		else if (((t_node *)aux->content)->prompts[0] == '.')
		{
			manage_points(((t_node *)aux->content)->prompts, env->pwd);
		}
		else
		{
			
		}
		
	}
}