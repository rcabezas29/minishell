/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 12:15:10 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/13 15:47:07 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse(char *prompt, t_env *env)
{
	int	i;
	char **commands;

	i = 0;
	commands = ft_split(prompt, ' ');
	execute_commands(commands[0], env);
}

void	read_commands(char **commands, t_env *env)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (ft_strchr(commands[i], '='))
			define_env_variable(commands[i]);
		else
			execute_commands(commands[i], env);
	}
}