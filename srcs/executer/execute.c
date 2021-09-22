/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:15:28 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/22 13:28:14 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute(t_cmd_info *cmd_info, t_env *env)
{
	
}

char	*cmd_path(t_env *env, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;
	int		check_path;

	path = NULL;
	i = 0;
	while (env->paths[i])
	{
		tmp = ft_strjoin(ft_strjoin(env->paths[i], "/"), ft_split(cmd, ' ')[0]);
		check_path = open(tmp, O_RDONLY);
		if (check_path < 0)
			i++;
		else
		{
			path = tmp;
			break ;
		}
	}
	if (!path)
	{
		ft_putstr(ft_strjoin(cmd, ": command not found"));
		exit(EXIT_SUCCESS);
	}
	return (path);
}