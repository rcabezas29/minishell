/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:01:26 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/14 13:29:07 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*parse(char *prompt, t_env *env)
{
	int		i;
	t_list	*command_line;
	char	*word;

	i = 0;
	while (prompt[i])
	{
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\'')
		{
			i++;
			while (prompt[i] != '\'')
			{
				*word = prompt[i];
				word++;
				i++;
			}
			add_word_to_list(word, command_line);
		}
		else if (prompt[i] == '\"')
		{
			i++;
			while (prompt[i] != '\"')
			{
				*word = prompt[i];
				word++;
				i++;
			}
			add_word_to_list(word, command_line);
		}
		else
		{
			while (prompt[i] != ' ')
			{
				*word = prompt[i];
				word++;
				*word = '\0';
				i++;
			}
			add_word_to_list(word, command_line);
		}
		i++;
	}
	return (command_line);
}

void	add_word_to_list(char *word, t_list *command_line)
{
	t_node	*node;

	node->content = word;
	if (!ft_strncmp(word, "<", 1))
		node->type == INDIRECTION;
	else if (!ft_strncmp(word, ">", 1))
		node->type == REDIRECTION;
	else if (!ft_strncmp(word, "<<", 2))
		node->type == HERE_DOC;
	else if (!ft_strncmp(word, ">>", 2))
		node->type == APPEND;
	else if (!ft_strncmp(word, "|", 1))
		node->type == PIPE;
	else
		
	ft_lstadd_back(command_line, node);
}