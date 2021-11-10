/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/10 09:10:41 by rcabezas         ###   ########.fr       */
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

char	*memory_main(int argc, char **argv, t_env *env, char **envp)
{
	char			*prom;

	argc = 0;
	argv = NULL;
	take_envs(envp, env);
	sig_init();
	prom = readline("\033[0;32mminishell - \033[0;0m");
	if (!prom)
		exit(0);
	if (prom[0] != '\0')
		add_history(prom);
	return (prom);
}

void	print_exe(t_exe *exe)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		printf("FD_IN %i\nCMD %s\nARG %s\nFD_OUT %i\n", exe[i].fd_in, exe[i].cmd, exe[i].args[0], exe[i].fd_out);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*env;
	t_cmd_info		*cmd_info;
	char			*prompt;
	struct termios	old;

	cmd_info = ft_calloc(sizeof(t_cmd_info), 1);
	env = ft_calloc(sizeof(t_env), 1);
	tcgetattr(0, &old);
	prompt = memory_main(argc, argv, env, envp);
	while (1)
	{
		if (prompt[0] != '\0')
		{
			add_history(prompt);
			lexer(env, cmd_info, prompt);
			analyze_prompt(cmd_info, env);
			parser(cmd_info);
			print_exe(cmd_info->exe);
			//execute(cmd_info, env);
			ft_lstclear(&cmd_info->command_list, del);
		}
		else
			free (prompt);
		tcsetattr(0, TCSANOW, &old);
		prompt = readline("\033[0;32mminishell - \033[0;0m");
	}
	return (0);
}
