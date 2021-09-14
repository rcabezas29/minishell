/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:01:26 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/14 11:00:01 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*parse(char *prompt, t_env *env)
{
	int		i;
	int		j;
	int		k;
	t_list	*command_line;
	char	*word;

	i = 0;
	j = 0;
	while (prompt[i])
	{
		if (prompt[i] != '|' && prompt[i] != '\'' && prompt[i] != '\"')
		{
			k = 0;
			while (prompt[i] == ' ')
				i++;
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
		
	if (!ft_strncmp(word, ">", 1))
		
}