/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:37:50 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/13 20:16:38 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_pwd(t_cmd_info *cmd_info)
{
	int	nargs;
	char	buf[FILENAME_MAX];

	nargs = count_arguments(cmd_info->command_list);
	if (nargs != 1)
	{
		perror("pwd: too many arguments\n");
		return ;
	}
	printf("%s\n", getcwd(buf, sizeof(buf)));
}
