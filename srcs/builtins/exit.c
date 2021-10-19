/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:13:53 by fballest          #+#    #+#             */
/*   Updated: 2021/10/19 21:10:07 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		alpha_in_string(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_cleanmemory(t_cmd_info *cmd_info, t_env *env)
{
	ft_lstclear(&cmd_info->command_list, del);
	ft_freematrix(env->paths);
	ft_freematrix(env->envp);
	free(env);
	free(cmd_info->command_list);
	free(cmd_info);
	clear_history();
	atexit(leaks);
}

void	execute_exit(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;
	int		nargs;
	int		ret;

	printf("exit\n");
	aux = cmd_info->command_list;
	nargs = count_arguments(aux);
	ret = 0;
	if (nargs == 1)
	{
		ft_cleanmemory(cmd_info, env);
		exit(0);
	}
	if (alpha_in_string(((t_node *)aux->next->content)->prompts))
	{
		printf("%s: numeric argument required", ((t_node *)aux->next->content)->prompts);
		ft_cleanmemory(cmd_info, env);
		exit(255);
	}
	if (count_arguments(aux) > 2)
	{
		printf("exit: too many arguments\n");
		cmd_info->return_code = 1;
	}
	else
	{
		ret = ft_atoi(((t_node *)aux->next->content)->prompts);
		ft_cleanmemory(cmd_info, env);
		exit(ret);
	}
}
