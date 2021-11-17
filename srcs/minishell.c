/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/17 14:36:32 by fballest         ###   ########.fr       */
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

static char 	*expand_mayorminor(char *prompt, int *i, int *j)
{
	char	*tmp;
	int		z;
	int		y;

	z = 0;
	tmp = ft_strdup(prompt);
	while (prompt[(*i)])
	{
		if (prompt[(*i)] == '>' && prompt[(*i) + 1] == '>'
			&& (prompt[(*i) + 2] != ' ' && prompt[(*i) - 1] != ' '))
			z = 2;
		else if (prompt[(*i)] == '<' && prompt[(*i) + 1] == '<'
			&& (prompt[(*i) + 2] != ' ' && prompt[(*i) - 1] != ' '))
			z = 2;
		else if (prompt[(*i)] == '>'
			&& (prompt[(*i) + 1] != ' ' || prompt[(*i) - 1] != ' '))
			z = 1;
		else if (prompt[(*i)] == '<'
			&& (prompt[(*i) + 1] != ' ' || prompt[(*i) - 1] != ' '))
			z = 1;
		else if (prompt[(*i)] == '|' && prompt[(*i) + 1] != ' ')
			z = 1;
		else if (prompt[(*i)] == '|' && prompt[(*i) + 1] == '|'
			&& prompt[(*i) + 2] == '|')
		{
			printf("Minishell: syntax error near unexpected token");
			return (NULL);
		}	
		else
			tmp[(*j)++] = prompt[(*i)++];
		while (z > 0)
		{
			if (tmp)
			{
				y = ft_strlen(tmp) + 5;
				tmp = ft_realloc(tmp, y);
				tmp[y - 1] = '\0';
			}
			else
				tmp = ft_strdup(prompt);
			tmp[(*j)++] = ' ';
			while (z > 0)
			{
				tmp[(*j)++] = prompt[(*i)];
				z--;
			}
			tmp[(*j)++] = ' ';
			(*i)++;
			z = (*i);
			while (prompt[z])
				tmp[(*j)++] = prompt[z++];
			tmp[(*j)] = '\0';
			z = 0;
			(*i) = (*i) + 2;
			(*j) = (*i);
			free (prompt);
			prompt = ft_strdup(tmp);
			return (prompt);
		}
	}
	return (prompt);
}

int		check_end_prompt(char *prompt, t_cmd_info *cmd_info)
{
	int		len;

	len = ft_strlen(prompt);
	if (prompt[len - 1] == '|' || prompt[len - 1] == '>'
		|| prompt[len - 1] == '<')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (cmd_info->return_code = 1);
	}
	return (0);
}

char	*check_prompt(char *prompt, t_cmd_info *cmd_info)
{
	char	*aux;
	int		s_quotes;
	int		d_quotes;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s_quotes = 0;
	d_quotes = 0;
	if (check_end_prompt(prompt, cmd_info) == 1)
		return (NULL);
	aux = ft_strdup(prompt);
	while (prompt[i])
	{
		if (prompt[i] == '\'' && (d_quotes == 0 || !(d_quotes % 2)))
		{
			if (prompt[i + 1] != '\'')
			{
				s_quotes += 1;
				aux[j++] = prompt[i++];
			}
			else
				i += 2;
		}
		else if (prompt[i] == '\"' && (s_quotes == 0 || !(s_quotes % 2)))
		{
			if (prompt[i + 1] != '\"')
			{
				d_quotes += 1;
				aux[j++] = prompt[i++];
			}
			else
				i += 2;
		}
		else if ((prompt[i] == '>' || prompt[i] == '<')
			&& ((d_quotes == 0 || (d_quotes % 2) == 0)
				&& (s_quotes == 0 || (s_quotes % 2) == 0)))
		{
			prompt = expand_mayorminor(prompt, &i, &j);
			aux = ft_realloc(prompt, i + 1);
			aux[i] = '\0';
			if (!prompt)
			{
				cmd_info->return_code = 1;
				return (NULL);
			}
		}
		else
		{
			aux[j++] = prompt[i++];
			aux[j] = '\0';
		}
	}
	aux[j] = '\0';
	prompt = ft_realloc(aux, ft_strlen(aux));
	if ((d_quotes > 0 && (d_quotes % 2)) || (s_quotes > 0 && (s_quotes % 2)))
	{
		printf("Minishell: systax error\n");
		cmd_info->return_code = 3;
		return (NULL);
	}
	return (prompt);
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
			free (prompt);
		reset_values(cmd_info);
		prompt = memory_main(argc, argv);
	}
	return (0);
}
