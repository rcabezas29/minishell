/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/11 11:31:55 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*prompt;

	argc = 0;
	argv = NULL;
	env = ft_calloc(sizeof(t_env), 1);
	env = take_envs(envp);

	prompt = readline("\033[0;32mminishell - \033[0;0m");
	while (ft_strcmp("exit", prompt))
	{
		prompt = readline("\033[0;32mminishell - \033[0;0m");
	}
	return (0);
}
