/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:01:26 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/15 12:48:04 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd_list	*parse(char *prompt, t_env *env)
{
	int			i;
	int			j;
	t_cmd_list	*command_line;
	char		word[20];

	i = 0;
	command_line = malloc(sizeof(t_cmd_list));
	while (prompt[i])
	{
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\'')
		{
			i++;
			j = 0;
			while (prompt[i] != '\'')
			{
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
			while (prompt[i] != ' ' && prompt[i])
			{
				word[j] = prompt[i];
				j++;
				i++;
			}
			word[j] = '\0';
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

	node = malloc(sizeof(t_node));
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

void	ft_cmdlstadd_back(t_cmd_list *alst, t_node *node)
{
	t_cmd_list	*tmp;

	tmp = malloc(sizeof(t_cmd_list));
	tmp = alst;
	if (tmp == NULL)
		tmp->content = node;
	else
	{
		tmp = ft_cmdlstlast(alst);
		tmp->content = node;
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
