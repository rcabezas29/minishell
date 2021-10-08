/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:37:50 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/08 09:57:50 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_pwd(t_cmd_info *cmd_info, t_env *env)
{
	int	nargs;

	nargs = count_arguments(cmd_info->command_list);
	if (nargs != 1)
	{
		perror("pwd: too many arguments\n");
		return ;
	}
	ft_putstr(env->pwd);
	write(1, "\n", 1);
}
