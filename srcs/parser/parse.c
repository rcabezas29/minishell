/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:01:26 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/07 12:50:37 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*parse_simple_chars(char *prompt, int *i)
{
	char	*word;
	int		j;

	j = 0;
	word = malloc(sizeof(char));
	word[0] = '\0';
	while (prompt[*i] != '\0' && prompt[*i] != ' ')
	{
		if (prompt[*i] == '\'')
		{
			(*i)++;
			while (prompt[*i] && prompt[*i] != '\'')
			{
				word = ft_realloc(word, (ft_strlen(word) + 1));
				word[j] = prompt[*i];
				j++;
				word[j] = '\0';
				(*i)++;
			}
			if (prompt[*i] != '\'')
				(*i)++;
		}
		else if (prompt[*i] == '\"')
		{
			(*i)++;
			while (prompt[*i] && prompt[*i] != '\"')
			{
				word = ft_realloc(word, (ft_strlen(word) + 1));
				word[j] = prompt[*i];
				j++;
				word[j] = '\0';
				(*i)++;
			}
			if (prompt[*i] != '\"')
				(*i)++;
		}
		else
		{
			if (!prompt[*i])
				break ;
			word = ft_realloc(word, (ft_strlen(word) + 1));
			word[j] = prompt[*i];
			j++;
			word[j] = '\0';
			(*i)++;
		}
	}
	return (word);
}

static char	*parse_quotes(char *prompt, int *i, char c)
{
	char	*word;
	int		j;

	(*i)++;
	j = 0;
	word = malloc(sizeof(char));
	word[0] = '\0';
	while (prompt[*i] != c && prompt[*i + 1] && prompt[*i + 1] != ' ')
	{
		word = ft_realloc(word, (ft_strlen(word) + 1));
		word[j] = prompt[*i];
		j++;
		word[j] = '\0';
		(*i)++;
	}
	return (word);
}

void	parse(t_cmd_info *cmd_info, char *prompt)
{
	int		i;
	char	*word;
	int		prompt_len;

	i = 0;
	prompt_len = (int)ft_strlen(prompt);
	while (i < prompt_len)
	{
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\'')
		{
			word = parse_quotes(prompt, &i, '\'');
			add_word_to_list(&cmd_info->command_list, cmd_info, word);
		}
		else if (prompt[i] == '\"')
		{
			word = parse_quotes(prompt, &i, '\"');
			add_word_to_list(&cmd_info->command_list, cmd_info, word);
		}
		else
		{
			word = parse_simple_chars(prompt, &i);
			add_word_to_list(&cmd_info->command_list, cmd_info, word);
		}
		free(word);
		word = NULL;
		i++;
	}
}

void	add_word_to_list(t_list **list, t_cmd_info *cmd_info, char *word)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
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

void	analyze_prompt(t_cmd_info *cmd_info)
{
	t_list	*aux;

	aux = cmd_info->command_list;
	if (((t_node *)aux->content)->types == 1)
		perror("syntax error near unexpected token `|'");
	if (((t_node *)aux->content)->types > 1
		&& ((t_node *)aux->content)->types < 6)
	{
		/////// primer argumento redirecciones
		aux = aux->next;
		((t_node *)aux->content)->types = FILE_NAME ;
		if (aux->next)
			aux = aux->next;
	}
	while (aux && ((t_node *)aux->content)->types != 1)
	{
		if (((t_node *)aux->content)->types > 1
			&& ((t_node *)aux->content)->types < 6)
		{
			/////// redirecciones
			aux = aux->next;
			((t_node *)aux->content)->types = FILE_NAME;
		}
		else if (((t_node *)aux->content)->types == 0)
		{
			check_builtins(cmd_info);
		}
		aux = aux->next;
	}
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
