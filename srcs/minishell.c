/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/27 10:40:28 by fballest         ###   ########.fr       */
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

void	del(void *node)
{
	free(((t_node *)node)->prompts);
	((t_node *)node)->prompts = NULL;
	((t_node *)node)->types = 0;
	((t_node *)node)->built_in = 0;
	free((t_node *)node);
}

char	*memory_main(t_env *env, char **envp)
{
	char			*prom;

	take_envs(envp, env);
	sig_init();
	prom = readline("\033[0;32mminishell - \033[0;0m");
	if (!prom)
		exit(0);
	if (prom[0] != '\0')
		add_history(prom);
	return (prom);
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*env;
	t_cmd_info		*cmd_info;
	char			*prompt;

	argc = 0;
	argv = NULL;
	cmd_info = ft_calloc(sizeof(t_cmd_info), 1);
	env = ft_calloc(sizeof(t_env), 1);
	prompt = memory_main(env, envp);
	while (1)
	{
		if (prompt[0] != '\0')
		{
			add_history(prompt);
			lexer(env, cmd_info, prompt);
			analyze_prompt(cmd_info);
			execute(cmd_info, env);
			ft_lstclear(&cmd_info->command_list, del);
		}
		prompt = readline("\033[0;32mminishell - \033[0;0m");
		if (!prompt)
			exit(0);
	}
	return (0);
}
