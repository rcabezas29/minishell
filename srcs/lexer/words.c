/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:43:56 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/28 15:58:56 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	word_analyzer(t_parser *p, t_env *env, t_cmd_info *cmd_info)
{
	p->word = ft_calloc(sizeof(char), 1);
	while (p->prompt[p->i] == ' ')
		p->i++;
	if (p->prompt[p->i] == '\'')
	{
		parse_quotes(env, p, '\'', cmd_info);
		add_word_to_list(&cmd_info->command_list, cmd_info, p->word);
	}
	else if (p->prompt[p->i] == '\"')
	{
		parse_quotes(env, p, '\"', cmd_info);
		add_word_to_list(&cmd_info->command_list, cmd_info, p->word);
	}
	else
	{
		parse_simple_chars(env, p, cmd_info, 0);
		add_word_to_list(&cmd_info->command_list, cmd_info, p->word);
	}
	free(p->word);
	p->i++;
}

void	add_word_to_list(t_list **list, t_cmd_info *cmd_info, char *word)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node), 1);
	node->prompts = ft_strdup(word);
	if (!ft_strncmp(word, "<<", 2))
		node->types = HERE_DOC;
	else if (!ft_strncmp(word, ">>", 2))
		node->types = APPEND;
	else if (!ft_strncmp(word, "<", 1))
		node->types = INDIRECTION;
	else if (!ft_strncmp(word, ">", 1))
		node->types = REDIRECTION;
	else if (!ft_strncmp(word, "|", 1))
	{
		node->types = PIPE;
		cmd_info->no_pipes++;
	}
	else
		node->types = ARGUMENT;
	ft_lstadd_back(list, ft_lstnew(node));
}
