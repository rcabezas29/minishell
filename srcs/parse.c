/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:01:26 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/15 10:07:13 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd_list	*parse(char *prompt, t_env *env)
{
	int		i;
	t_cmd_list	*command_line;
	char	*word;

	i = 0;
	command_line = NULL;
	word = NULL;
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
	env->home = NULL; //////////////////
	return (command_line);
}

void	add_word_to_list(char *word, t_cmd_list *command_line)
{
	t_node	*node;

	node = NULL;
	node->content = word;
	if (!ft_strncmp(word, "<", 1))
		node->type = INDIRECTION;
	else if (!ft_strncmp(word, ">", 1))
		node->type = REDIRECTION;
	else if (!ft_strncmp(word, "<<", 2))
		node->type = HERE_DOC;
	else if (!ft_strncmp(word, ">>", 2))
		node->type = APPEND;
	else if (!ft_strncmp(word, "|", 1))
		node->type = PIPE;
	else
		node->type = ARGUMENT;
	ft_cmdlstadd_back(command_line, node);
}

void	ft_cmdlstadd_back(t_cmd_list *alst, t_node *new)
{
	t_cmd_list	*tmp;

	if (alst)
	{
		if (alst == NULL)
			alst->content = new;
		else
		{
			tmp = ft_cmdlstlast(alst);
			tmp->next->content = new;
		}
	}
}

t_cmd_list	*ft_cmdlstlast(t_cmd_list *lst)
{
	t_cmd_list	*tmp;

	tmp = lst;
	if (lst)
		while (tmp->next)
			tmp = tmp->next;
	return (tmp);
}
