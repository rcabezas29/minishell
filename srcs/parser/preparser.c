/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:40:35 by fballest          #+#    #+#             */
/*   Updated: 2021/12/03 18:13:05 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	expand_conditions(char *prompt, char *tmp, int **i, int **j)
{
	int		z;

	z = 0;
	if (prompt[(**i)] == '>' && prompt[(**i) + 1] == '>')
		z = 2;
	else if (prompt[(**i)] == '<' && prompt[(**i) + 1] == '<')
		z = 2;
	else if (prompt[(**i)] == '>')
		z = 1;
	else if (prompt[(**i)] == '<')
		z = 1;
	else
		tmp[(**j)++] = prompt[(**i)++];
	return (z);
}

static char	*check_tmpmemory(char *prompt, char *tmp, int *z, int *y)
{
	if (tmp)
	{
		(*y) = (ft_strlen(tmp) + (*z) + 3);
		tmp = ft_realloc(tmp, (*y));
		tmp[(*y) - 1] = '\0';
	}
	else
		tmp = ft_strdup(prompt);
	return (tmp);
}

char	*expand_mayorminor(char *prompt, int *i, int *j)
{
	char	*tmp;
	int		y;
	int		z;

	tmp = ft_strdup(prompt);
	while (prompt[(*i)])
	{
		z = expand_conditions(prompt, tmp, &i, &j);
		while (z > 0)
		{
			tmp = check_tmpmemory(prompt, tmp, &z, &y);
			tmp[(*j)++] = ' ';
			while (z > 0)
			{
				tmp[(*j)++] = prompt[(*i)++];
				z--;
			}
			tmp[(*j)++] = ' ';
			z = (*i)++;
			while (prompt[z])
				tmp[(*j)++] = prompt[z++];
			tmp[(*j)] = '\0';
			z = 0;
			(*j) = (*i) + 2;
			(*i) = (*j);
			free (prompt);
			return (tmp);
		}
	}
	return (prompt);
}

int	check_end_prompt(char *prompt, t_cmd_info *cmd_info)
{
	int		len;

	len = ft_strlen(prompt);
	if (prompt[len - 1] == '|' || prompt[len - 1] == '>'
		|| prompt[len - 1] == '<')
	{
		write(2, "minishell: syntax error near unexpected token `newline'\n", 57);
		return (cmd_info->return_code = 258);
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
			if (prompt[i + 1] != '\'')
			{
				s_quotes += 1;
				if (prompt[i + 1] == '\"'
					&& (s_quotes == 0 || !(s_quotes % 2)))
				{
					d_quotes += 1;
					i += 2;
				}
				else
					aux[j++] = prompt[i++];
			}
			else
				i += 2;
		}
		else if (prompt[i] == '\"' && (s_quotes == 0 || !(s_quotes % 2)))
		{
			if (prompt[i + 1] != '\"')
			{
				d_quotes += 1;
				if (prompt[i + 1] == '\''
					&& (d_quotes == 0 || !(d_quotes % 2)))
				{
					s_quotes += 1;
					i += 2;
				}
				else
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
		printf("minishell: syntax error\n");
		cmd_info->return_code = 3;
		return (NULL);
	}
	free (prompt);
	return (aux);
}
