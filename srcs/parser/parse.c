/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:01:26 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/21 16:23:51 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_simple_chars(t_env *env, t_parser *p, t_cmd_info *cmd_info)
{
	int		j;

	j = 0;
	while (p->prompt[p->i] != '\0' && p->prompt[p->i] != ' ')
	{
		if (p->prompt[p->i] == '\'')
		{
			p->i++;
			while (p->prompt[p->i] && p->prompt[p->i] != '\'')
			{
				p->word = ft_realloc(p->word, (ft_strlen(p->word) + 2));
				p->word[j] = p->prompt[p->i];
				j++;
				p->word[j] = '\0';
				p->i++;
			}
			if (p->prompt[p->i] != '\'')
				p->i++;
		}
		else if (p->prompt[p->i] == '\"')
		{
			p->i++;
			while (p->prompt[p->i] && p->prompt[p->i] != '\"')
			{
				if (p->prompt[p->i] == '$')
					expand_dollars(env, p, &j, cmd_info);
				if (p->prompt[p->i] == '$')
					continue ;
				if (p->prompt[p->i] == '\"')
					p->i++;
				p->word = ft_realloc(p->word, (ft_strlen(p->word) + 2));
				p->word[j] = p->prompt[p->i];
				j++;
				p->word[j] = '\0';
				p->i++;
			}
		}
		else
		{
			if (!p->prompt[p->i])
				break ;
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
				if (p->prompt[p->i] == '$' && (p->prompt[p->i + 1] && p->prompt[p->i + 1] != '\"' && p->prompt[p->i + 1] != '\''))
					continue ;
			}
			p->word = ft_realloc(p->word, (ft_strlen(p->word) + 2));
			p->word[j] = p->prompt[p->i];
			j++;
			p->word[j] = '\0';
			p->i++;
		}
	}
}

void	parse_quotes(t_env *env, t_parser *p, char c, t_cmd_info *cmd_info)
{
	int		j;

	p->i++;
	j = 0;
	while (p->prompt[p->i] != c && p->prompt[p->i + 1])
	{
		if (p->prompt[p->i] == '$' && c == '\"')
			expand_dollars(env, p, &j, cmd_info);
		if (p->prompt[p->i] == c)
			return ;
		p->word = ft_realloc(p->word, (ft_strlen(p->word) + 2));
		p->word[j] = p->prompt[p->i];
		j++;
		p->word[j] = '\0';
		p->i++;
	}
}

void	parse(t_env *env, t_cmd_info *cmd_info, char *prompt)
{
	t_parser	*p;
	int			prompt_len;

	p = ft_calloc(sizeof(t_parser), 1);
	p->prompt = ft_strdup(prompt);
	prompt_len = (int)ft_strlen(prompt);
	while (p->i < prompt_len)
	{
		p->word = ft_calloc(sizeof(char), 1);
		while (prompt[p->i] == ' ')
			p->i++;
		if (prompt[p->i] == '\'')
		{
			parse_quotes(env, p, '\'', cmd_info);
			add_word_to_list(&cmd_info->command_list, cmd_info, p->word);
		}
		else if (prompt[p->i] == '\"')
		{
			parse_quotes(env, p, '\"', cmd_info);
			add_word_to_list(&cmd_info->command_list, cmd_info, p->word);
		}
		else
		{
			parse_simple_chars(env, p, cmd_info);
			add_word_to_list(&cmd_info->command_list, cmd_info, p->word);
		}
		free(p->word);
		p->i++;
	}
	free(prompt);
	prompt = NULL;
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

void	analyze_prompt(t_cmd_info *cmd_info)
{
	t_list	*aux;

	aux = cmd_info->command_list;
	if (((t_node *)aux->content)->types == 1)
		perror("syntax error near unexpected token `|'\n");
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
			ft_redirections(cmd_info);
			aux = aux->next;
			((t_node *)aux->content)->types = FILE_NAME;
		}
		else if (((t_node *)aux->content)->types == 0)
		{
			check_builtins(cmd_info);
		}
		//while (((t_node *)aux->content)->types == 0)
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
