/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:40:35 by fballest          #+#    #+#             */
/*   Updated: 2021/11/18 09:48:40 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_mayorminor(char *prompt, int *i, int *j)
{
	char	*tmp;
	int		z;
	int		y;

	z = 0;
	tmp = ft_strdup(prompt);
	while (prompt[(*i)])
	{
		if (prompt[(*i)] == '>' && prompt[(*i) + 1] == '>')
			z = 2;
		else if (prompt[(*i)] == '<' && prompt[(*i) + 1] == '<')
			z = 2;
		else if (prompt[(*i)] == '>')
			z = 1;
		else if (prompt[(*i)] == '<')
			z = 1;
		else
			tmp[(*j)++] = prompt[(*i)++];
		while (z > 0)
		{
			if (tmp)
			{
				y = ft_strlen(tmp) + z + 2;
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
			return (tmp);
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
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '\'' && (d_quotes == 0 || !(d_quotes % 2)))
		{
			if (prompt[i + 1] != '\'' || prompt[i + 1] != '\"')
			{
				s_quotes += 1;
				aux[j++] = prompt[i++];
			}
			else
				i += 2;
		}
		else if (prompt[i] == '\"' && (s_quotes == 0 || !(s_quotes % 2)))
		{
			if (prompt[i + 1] != '\"' || prompt[i + 1] != '\'')
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
			free (aux);
			aux = ft_strdup(prompt);
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
	if ((d_quotes > 0 && (d_quotes % 2)) || (s_quotes > 0 && (s_quotes % 2)))
	{
		printf("Minishell: systax error\n");
		cmd_info->return_code = 3;
		return (NULL);
	}
	free (prompt);
	return (aux);
}