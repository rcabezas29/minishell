/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:01:26 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/20 10:18:02 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*parse(char *prompt, t_env *env)
{
	int			i;
	int			j;
	t_list		*command_line;
	char		*word;

	i = 0;
	command_line = NULL;
	while (prompt[i])
	{
		word = malloc(sizeof(char));
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\'')
		{
			i++;
			j = 0;
			while (prompt[i] != '\'')
			{
				word = ft_realloc(word, sizeof(word) + 1);
				word[j] = prompt[i];
				j++;
				word[j] = '\0';
				i++;
			}
			add_word_to_list(word, command_line);
		}
		else if (prompt[i] == '\"')
		{
			i++;
			j = 0;
			while (prompt[i] != '\"')
			{
				word = ft_realloc(word, sizeof(word) + 1);
				word[j] = prompt[i];
				j++;
				i++;
			}
			word[j] = '\0';
			add_word_to_list(word, command_line);
		}
		else
		{
			j = 0;
			while (prompt[i] && prompt[i] != ' ')
			{
				word = ft_realloc(word, sizeof(word) + 1);
				word[j] = prompt[i];
				j++;
				i++;
			}
			word[j] = '\0';
			add_word_to_list(word, command_line);
		}
		free(word);
		i++;
	}
	env->home = NULL; //////////////////
	return (command_line);
}

void	add_word_to_list(char *word, t_list *command_line)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->prompts = ft_strdup(word);
	if (!ft_strncmp(word, "<", 1))
		node->types = INDIRECTION;
	else if (!ft_strncmp(word, ">", 1))
		node->types = REDIRECTION;
	else if (!ft_strncmp(word, "<<", 2))
		node->types = HERE_DOC;
	else if (!ft_strncmp(word, ">>", 2))
		node->types = APPEND;
	else if (!ft_strncmp(word, "|", 1))
		node->types = PIPE;
	else
		node->types = ARGUMENT;
	ft_lstadd_back(&command_line, ft_lstnew(node));
}

void	analyze_prompt(t_list *command_list)
{
	t_list	*aux;

	aux = command_list;
	while(((t_node *)aux->content)->types != 1)
	{
		if (((t_node *)aux->content)->prompts == )

	}
}
