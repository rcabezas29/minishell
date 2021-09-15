/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/15 12:46:47 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	leaks(void)
{
	system("leaks minishell");
}

void	print_list(t_cmd_list *command_list)
{
	t_cmd_list	*tmp;

	tmp = command_list;
	while (tmp)
	{
		printf("%s\n", tmp->content->content);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;
	t_cmd_list	*command_list;
	char		*prompt;

	argc = 0;
	argv = NULL;
	env = ft_calloc(sizeof(t_env), 1);
	env = take_envs(envp);
	prompt = readline("\033[0;32mminishell - \033[0;0m");
	add_history(prompt);
	while (ft_strcmp("exit", prompt))
	{
		command_list = parse(prompt, env);
		print_list(command_list);
		prompt = readline("\033[0;32mminishell - \033[0;0m");
		add_history(prompt);
	}
	atexit(leaks);
	return (0);
}
