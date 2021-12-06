/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:40:35 by fballest          #+#    #+#             */
/*   Updated: 2021/12/06 11:16:07 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static int	expand_conditions(char *prompt, char *tmp, t_pparse *pp)
// {
// 	int		z;

// 	z = 0;
// 	if (prompt[pp->i] == '>' && prompt[pp->i + 1] == '>')
// 		z = 2;
// 	else if (prompt[pp->i] == '<' && prompt[pp->i + 1] == '<')
// 		z = 2;
// 	else if (prompt[pp->i] == '>')
// 		z = 1;
// 	else if (prompt[pp->i] == '<')
// 		z = 1;
// 	else
// 		tmp[pp->j++] = prompt[pp->i++];
// 	return (z);
// }

// static char	*check_tmpmemory(char *prompt, char *tmp, int *z, int *y)
// {
// 	if (tmp)
// 	{
// 		(*y) = (ft_strlen(tmp) + (*z) + 3);
// 		tmp = ft_realloc(tmp, (*y));
// 		tmp[(*y) - 1] = '\0';
// 	}
// 	else
// 		tmp = ft_strdup(prompt);
// 	return (tmp);
// }

// char	*expand_mayorminor_b(char *prompt, char *tmp, t_pparse *pp, int *z)
// {
// 	tmp[pp->j++] = ' ';
// 	(*z) = pp->i++;
// 	while (prompt[(*z)])
// 		tmp[pp->j++] = prompt[(*z)++];
// 	tmp[pp->j] = '\0';
// 	(*z) = 0;
// 	pp->j = pp->i + 2;
// 	pp->i = pp->j;
// 	free (prompt);
// 	return (tmp);
// }

// char	*expand_mayorminor(char *prompt, t_pparse *pp)
// {
// 	char	*tmp;
// 	int		y;
// 	int		z;

// 	tmp = ft_strdup(prompt);
// 	y = 0;
// 	while (prompt[(pp->i)])
// 	{
// 		z = expand_conditions(prompt, tmp, pp);
// 		while (z > 0)
// 		{
// 			tmp = check_tmpmemory(prompt, tmp, &z, &y);
// 			tmp[pp->j++] = ' ';
// 			while (z > 0)
// 			{
// 				tmp[pp->j++] = prompt[pp->i++];
// 				z--;
// 			}
// 			tmp = expand_mayorminor_b(prompt, tmp, pp, &z);
// 			return (tmp);
// 		}
// 	}
// 	return (prompt);
// }

// int	check_end_prompt(char *prompt, t_cmd_info *cmd_info)
// {
// 	int		len;

// 	len = ft_strlen(prompt);
// 	if (prompt[len - 1] == '|' || prompt[len - 1] == '>'
// 		|| prompt[len - 1] == '<')
// 	{
// 		write(2,
// 			"minishell: syntax error near unexpected token `newline'\n", 57);
// 		return (cmd_info->return_code = 258);
// 	}
// 	return (0);
// }

// void	check_simplequotes(char *prompt, t_pparse *pp)
// {
// 	if (prompt[pp->i + 1] != '\'')
// 	{
// 		pp->s_quotes += 1;
// 		if (prompt[pp->i + 1] == '\"'
// 			&& (pp->s_quotes == 0 || !(pp->s_quotes % 2)))
// 		{
// 			pp->d_quotes += 1;
// 			pp->i += 2;
// 		}
// 		else
// 			pp->aux[pp->j++] = prompt[pp->i++];
// 	}
// 	else
// 		pp->i += 2;
// }

char	*check_finish(char *prompt, t_cmd_info *cmd_info, t_pparse *pp)
{
	pp->aux[pp->j] = '\0';
	if ((pp->d_quotes > 0 && (pp->d_quotes % 2))
		|| (pp->s_quotes > 0 && (pp->s_quotes % 2)))
	{
		printf("minishell: syntax error\n");
		cmd_info->return_code = 3;
		return (NULL);
	}
	free (prompt);
	prompt = ft_strdup(pp->aux);
	free (pp->aux);
	free (pp);
	return (prompt);
}

void	check_doublequotes(char *prompt, t_pparse *pp)
{
	if (prompt[pp->i + 1] != '\"')
	{
		pp->d_quotes += 1;
		if (prompt[pp->i + 1] == '\''
			&& (pp->d_quotes == 0 || !(pp->d_quotes % 2)))
		{
			pp->s_quotes += 1;
			pp->i += 2;
		}
		else
			pp->aux[pp->j++] = prompt[pp->i++];
	}
	else
		pp->i += 2;
}

void	check_addletter(char *prompt, t_pparse *pp)
{
	pp->aux[pp->j++] = prompt[pp->i++];
	pp->aux[pp->j] = '\0';
}

char	*check_prompt_b(char *prompt, t_cmd_info *cmd_info, t_pparse *pp)
{
	prompt = expand_mayorminor(prompt, pp);
	free (pp->aux);
	pp->aux = ft_strdup(prompt);
	if (!prompt)
	{
		cmd_info->return_code = 1;
		return (NULL);
	}
	return (prompt);
}

char	*check_prompt(char *prompt, t_cmd_info *cmd_info)
{
	t_pparse	*pp;

	pp = ft_calloc(sizeof(t_pparse), 1);
	if (check_end_prompt(prompt, cmd_info) == 1)
		return (NULL);
	pp->aux = ft_strdup(prompt);
	while (prompt[pp->i] != '\0')
	{
		if (prompt[pp->i] == '\'' && (pp->d_quotes == 0 || !(pp->d_quotes % 2)))
			check_simplequotes(prompt, pp);
		else if (prompt[pp->i] == '\"' && (pp->s_quotes == 0
				|| !(pp->s_quotes % 2)))
			check_doublequotes(prompt, pp);
		else if ((prompt[pp->i] == '>' || prompt[pp->i] == '<')
			&& ((pp->d_quotes == 0 || (pp->d_quotes % 2) == 0)
				&& (pp->s_quotes == 0 || (pp->s_quotes % 2) == 0)))
		{
			prompt = check_prompt_b(prompt, cmd_info, pp);
			if (!prompt)
				return (NULL);
		}
		else
			check_addletter(prompt, pp);
	}
	return (check_finish(prompt, cmd_info, pp));
}
