/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/23 18:02:27 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	free_exe(t_cmd_info *cmd_info)
{
	int	i;

	i = 0;
	while (i < cmd_info->no_pipes)
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
	cmd_info->exe = NULL;
	cmd_info->no_pipes = 0;
	cmd_info->return_code = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*env;
	t_cmd_info		*cmd_info;
	char			*prompt;
	struct termios	old;

	cmd_info = ft_calloc(sizeof(t_cmd_info), 1);
	env = ft_calloc(sizeof(t_env), 1);
	take_envs(envp, env);
	tcgetattr(0, &old);
	prompt = memory_main(argc, argv);
	while (1)
	{
		if (prompt[0] != '\0')
		{
			add_history(prompt);
			prompt = check_prompt(prompt, cmd_info);
			if (!prompt)
			{
				free(prompt);
				prompt = memory_main(argc, argv);
				continue ;
			}
			lexer(env, cmd_info, prompt);
			analyze_prompt(cmd_info, env);
			parser(cmd_info);
			execute(cmd_info, env);
		}
		else
			free(prompt);
		tcsetattr(0, TCSANOW, &old);
		reset_values(cmd_info);
		prompt = memory_main(argc, argv);
	}
	return (0);
}
