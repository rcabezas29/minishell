/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/16 19:36:14 by rcabezas         ###   ########.fr       */
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
			printf("----------------------------------------\n");
		}
		tmp = tmp->next;
	}
}

void	del(void *node)
{
	free(((t_node *)node)->prompts);
	((t_node *)node)->prompts = NULL;
	((t_node *)node)->types = 0;
	free((t_node *)node);
}

char	*memory_main(int argc, char **argv)
{
	char			*prom;

	argc = 0;
	argv = NULL;
	sig_init();
	prom = readline("\033[0;32mminishell - \033[0;0m");
	if (!prom)
		exit(0);
	if (prom[0] != '\0')
		add_history(prom);
	return (prom);
}

void	reset_values(t_cmd_info *cmd_info)
{
	ft_lstclear(&cmd_info->command_list, del);
	free(cmd_info->exe);
	cmd_info->exe = NULL;
	cmd_info->no_pipes = 0;
	cmd_info->return_code = 0;
}

int	check_prompt(char **prompt)
{
	int	len;

	len = ft_strlen(*prompt);
	if ((*prompt)[len - 1] == '|' || (*prompt)[len - 1] == '>' || (*prompt)[len - 1] == '<')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*env;
	t_cmd_info		*cmd_info;
	char			*prompt;

	cmd_info = ft_calloc(sizeof(t_cmd_info), 1);
	env = ft_calloc(sizeof(t_env), 1);
	take_envs(envp, env);
	prompt = memory_main(argc, argv);
	while (1)
	{
		if (prompt[0] != '\0')
		{
			if (!check_prompt(&prompt))
			{
				free(prompt);
				prompt = memory_main(argc, argv);
				continue ;
			}
			add_history(prompt);
			lexer(env, cmd_info, prompt);
			analyze_prompt(cmd_info, env);
			parser(cmd_info);
			execute(cmd_info, env);
		}
		else
			free (prompt);
		reset_values(cmd_info);
		prompt = memory_main(argc, argv);
	}
	return (0);
}
