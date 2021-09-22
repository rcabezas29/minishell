/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/22 19:30:32 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	leaks(void)
{
	system("leaks minishell");
}

void	print_list(t_cmd_info *cmd_info)
{
	t_list	*tmp;

	tmp = cmd_info->command_list;
	while (tmp)
	{
		if (((t_node *)tmp->content))
		{
			printf("%s\n", ((t_node *)tmp->content)->prompts);
			printf("%u\n", ((t_node *)tmp->content)->types);
			printf("%d\n", ((t_node *)tmp->content)->built_in);
			printf("----------------------------------------\n");
		}
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;
	t_cmd_info	*cmd_info;
	char		*prompt;

	argc = 0;
	argv = NULL;
	env = ft_calloc(sizeof(t_env), 1);
	cmd_info = ft_calloc(sizeof(t_cmd_info), 1);
	env = take_envs(envp);
	prompt = readline("\033[0;32mminishell - \033[0;0m");
	if (prompt[0] != '\0')
		add_history(prompt);
	while (ft_strcmp("exit", prompt))
	{
		if (prompt[0] != '\0')
		{
			add_history(prompt);
			cmd_info->command_list = parse(cmd_info, prompt);
			analyze_prompt(cmd_info);
			execute(cmd_info, env);
			//print_list(cmd_info);
			cmd_info->command_list = NULL;
		}
		prompt = readline("\033[0;32mminishell - \033[0;0m");
	}
	atexit(leaks);
	return (0);
}
