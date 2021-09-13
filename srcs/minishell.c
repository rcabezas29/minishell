/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/13 12:48:19 by rcabezas         ###   ########.fr       */
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
	char	*prompt;

	argc = 0;
	argv = NULL;
	env = ft_calloc(sizeof(t_env), 1);
	env = take_envs(envp);

	prompt = readline("\033[0;32mminishell - \033[0;0m");
	add_history(prompt);
	while (ft_strcmp("exit", prompt))
	{
		free(prompt);
		prompt = readline("\033[0;32mminishell - \033[0;0m");
		add_history(prompt);
		parse(prompt, env);
	}
	free(prompt);
	atexit(leaks);
	return (0);
}
