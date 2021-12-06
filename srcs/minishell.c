/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/06 18:12:27 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	leaks(void)
{
	system("leaks minishell");
}

void	del(void *node)
{
	free(((t_node *)node)->prompts);
	((t_node *)node)->prompts = NULL;
	((t_node *)node)->types = 0;
	free((t_node *)node);
}

char	*prompt_main(int argc, char **argv)
{
	char			*prompt;

	argc = 0;
	argv = NULL;
	prompt = readline("\033[0;32mminishell - \033[0;0m");
	if (!prompt)
		exit(0);
	if (prompt[0] != '\0')
		add_history(prompt);
	return (prompt);
}

void	free_exe(t_cmd_info *cmd_info)
{
	int	i;

	i = 0;
	while (i <= cmd_info->no_pipes)
	{
		free(cmd_info->exe[i].cmd);
		if (cmd_info->exe[i].args)
			ft_freematrix(cmd_info->exe[i].args);
		i++;
	}
}

void	reset_values(t_cmd_info *cmd_info)
{
	ft_lstclear(&cmd_info->command_list, del);
	free_exe(cmd_info);
	free(cmd_info->exe);
	cmd_info->no_pipes = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*env;
	t_cmd_info		*cmd_info;
	char			*prompt;

	cmd_info = ft_calloc(sizeof(t_cmd_info), 1);
	env = ft_calloc(sizeof(t_env), 1);
	atexit(leaks);
	take_envs(envp, env);
	while (1)
	{
		sig_init();
		prompt = prompt_main(argc, argv);
		if (prompt[0] != '\0')
		{
			prompt = check_prompt(prompt, cmd_info);
			lexer(env, cmd_info, prompt);
			analyze_prompt(cmd_info, env);
			parser(cmd_info);
			execute(cmd_info, env);
			reset_values(cmd_info);
		}
		free(prompt);
	}
	return (0);
}
