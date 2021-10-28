/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:01:26 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/28 16:00:31 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_next_char(t_parser *p, int *j)
{
	p->word = ft_realloc(p->word, (ft_strlen(p->word) + 2));
	p->word[*j] = p->prompt[p->i];
	(*j)++;
	p->word[*j] = '\0';
	p->i++;
}

int	check_dollar_to_print(t_parser *p)
{
	if (p->prompt[p->i] == '$'
		&& (p->prompt[p->i + 1]
			&& p->prompt[p->i + 1] != '\"'
			&& p->prompt[p->i + 1] != '\''))
		return (1);
	return (0);
}

void	parse_simple_chars(t_env *env, t_parser *p, t_cmd_info *cmd_info, int j)
{
	while (p->prompt[p->i] != '\0' && p->prompt[p->i] != ' ')
	{
		if (p->prompt[p->i] == '\'')
			simple_quotes_after_char(p, &j);
		else if (p->prompt[p->i] == '\"')
			double_quotes_after_char(p, env, cmd_info, &j);
		else
		{
			if (p->prompt[p->i] == '$')
			{
				if (p->prompt[p->i + 1] != '\'' && p->prompt[p->i + 1] != '\"')
					expand_dollars(env, p, &j, cmd_info);
				else
				{
					p->i++;
					parse_quotes(env, p, p->prompt[p->i], cmd_info);
					return ;
				}
				if (check_dollar_to_print(p))
					continue ;
			}
			set_next_char(p, &j);
		}
	}
}

void	lexer(t_env *env, t_cmd_info *cmd_info, char *prompt)
{
	t_parser	*p;
	int			prompt_len;

	p = ft_calloc(sizeof(t_parser), 1);
	p->prompt = ft_strdup(prompt);
	prompt_len = (int)ft_strlen(prompt);
	while (p->i < prompt_len)
		word_analyzer(p, env, cmd_info);
	free(prompt);
	prompt = NULL;
	free(p->prompt);
	p->prompt = NULL;
	free (p);
}

void	check_builtins(t_cmd_info *cmd_info)
{
	t_list	*aux;

	aux = cmd_info->command_list;
	if (!ft_strcmp(((t_node *)aux->content)->prompts, "echo")
		|| !ft_strcmp(((t_node *)aux->content)->prompts, "cd")
		|| !ft_strcmp(((t_node *)aux->content)->prompts, "pwd")
		|| !ft_strcmp(((t_node *)aux->content)->prompts, "env")
		|| !ft_strcmp(((t_node *)aux->content)->prompts, "export")
		|| !ft_strcmp(((t_node *)aux->content)->prompts, "unset")
		|| !ft_strcmp(((t_node *)aux->content)->prompts, "exit"))
		((t_node *)aux->content)->built_in = 1;
}
