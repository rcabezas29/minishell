/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/14 10:57:28 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	leaks()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_list *command_list;
	char	*prompt;

	argc = 0;
	argv = NULL;
	env = ft_calloc(sizeof(t_env), 1);
	env = take_envs(envp);

	prompt = readline("\033[0;32mminishell - \033[0;0m");
	add_history(prompt);
	while (ft_strcmp("exit", prompt))
	{
		command_list = parse(prompt, env);
		prompt = readline("\033[0;32mminishell - \033[0;0m");
		add_history(prompt);
	}
	atexit(leaks);
	return (0);
}
