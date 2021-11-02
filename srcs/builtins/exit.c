/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:13:53 by fballest          #+#    #+#             */
/*   Updated: 2021/11/02 12:37:57 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	alpha_in_string(char *str)
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
	//unlink(cmd_info->file);
	free(cmd_info->line);
	free(cmd_info);
	clear_history();
	atexit(leaks);
}

void	alpha_exit(t_cmd_info *cmd_info, t_env *env, char *alpha)
{
	printf("%s: numeric argument required", alpha);
	ft_cleanmemory(cmd_info, env);
	exit(255);
}

void	normal_exit(t_cmd_info *cmd_info, t_env *env, char *n)
{
	int	ret;

	ret = ft_atoi(n);
	ft_cleanmemory(cmd_info, env);
	exit(ret);
}

void	execute_exit(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;
	int		nargs;

	printf("exit\n");
	aux = cmd_info->command_list;
	nargs = count_arguments(aux);
	if (nargs == 1)
	{
		ft_cleanmemory(cmd_info, env);
		exit(0);
	}
	if (alpha_in_string(((t_node *)aux->next->content)->prompts))
		alpha_exit(cmd_info, env, ((t_node *)aux->next->content)->prompts);
	if (count_arguments(aux) > 2)
	{
		printf("exit: too many arguments\n");
		cmd_info->return_code = 1;
	}
	else
		normal_exit(cmd_info, env, ((t_node *)aux->next->content)->prompts);
}
