/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:40:35 by fballest          #+#    #+#             */
/*   Updated: 2021/12/08 10:32:19 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_tmpmemory(char *prompt, char *tmp, int *z, int *y)
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

char	*expand_mayorminor_b(char *prompt, char *tmp, t_pparse *pp, int *z)
{
	tmp[pp->j++] = ' ';
	while ((*z) > 0)
	{
		tmp[pp->j++] = prompt[pp->i++];
		(*z)--;
	}
	tmp[pp->j++] = ' ';
	(*z) = pp->i++;
	while (prompt[(*z)])
		tmp[pp->j++] = prompt[(*z)++];
	tmp[pp->j] = '\0';
	(*z) = 0;
	pp->j = pp->i + 2;
	pp->i = pp->j;
	free (prompt);
	prompt = ft_strdup(tmp);
	free (tmp);
	tmp = NULL;
	return (prompt);
}

char	*expand_mayorminor(char *prompt, t_pparse *pp)
{
	char	*tmp;
	int		y;
	int		z;

	tmp = ft_strdup(prompt);
	y = 0;
	while (prompt[(pp->i)])
	{
		z = expand_conditions(prompt, tmp, pp);
		if (z == 666)
		{
			write(2, "minishell: not supported redirection\n", 37);
			free (prompt);
			free (pp->aux);
			free (tmp);
			free (pp);
			return (NULL);
		}
		while (z > 0)
		{
			tmp = check_tmpmemory(prompt, tmp, &z, &y);
			tmp = expand_mayorminor_b(prompt, tmp, pp, &z);
			return (tmp);
		}
	}
	return (tmp);
}

int	check_end_prompt(char *prompt, t_cmd_info *cmd_info, t_pparse *pp)
{
	int		len;

	len = ft_strlen(prompt);
	while (len > 0 && prompt[len - 1] && prompt[len - 1] == ' ')
		len--;
	if (len > 0 && (prompt[len - 1] == '|' || prompt[len - 1] == '>'
			|| prompt[len - 1] == '<'))
	{
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 57);
		cmd_info->return_code = 258;
		free (prompt);
		prompt = NULL;
		free (pp);
		return (1);
	}
	return (0);
}

void	check_simplequotes(char *prompt, t_pparse *pp)
{
	if (prompt[pp->i + 1] != '\'')
	{
		pp->s_quotes += 1;
		if (prompt[pp->i + 1] == '\"'
			&& (pp->s_quotes == 0 || !(pp->s_quotes % 2)))
		{
			pp->d_quotes += 1;
			pp->i += 2;
		}
		else
			pp->aux[pp->j++] = prompt[pp->i++];
	}
	else
		pp->i += 2;
}
