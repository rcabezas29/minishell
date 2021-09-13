/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 12:15:10 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/13 13:21:17 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse(char *prompt, t_env *env)
{
	char	**pipes;
	char	**commands;
	int		i;

	pipes = ft_split(prompt, '|');
	i = 0;
	while (pipes[i])
	{
		commands = ft_split(pipes[i], ' ');
		i++;
	}
	if (i == 1)
		read_commands(commands, env);
	else
	{
		read_commands_to_pipes(commands, env, i);
	}
}

void	read_commands(char **commands, t_env *env)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (ft_strchr(commands[i], '='))
			define_env_variable(env, commands[i]);
		else
			execute_commands(commands[i], env);
	}
}