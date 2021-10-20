/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:42:46 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/20 11:28:06 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*copy_expanded_env(t_env *env, char *variable, int *j)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], variable, ft_strlen(variable)))
		{
			ret = ft_strdup(&env->envp[i][ft_strlen(variable) + 1]);
			break ;
		}
		i++;
	}
	(*j) += ft_strlen(ret);
	free(variable);
	return (ret);
}

static int	check_envi(t_env *env, char *variable)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], variable, ft_strlen(variable)))
			return (1);
		i++;
	}
	return (0);
}

void	expand_dollars(t_env *env, char *prompt, int *i, char **word, int *j, t_cmd_info *cmd_info)
{
	char	*variable;
	char	*aux;
	int		k;

	variable = malloc(sizeof(char));
	if (!ft_isalnum(prompt[*i + 1]) && prompt[*i + 1] != '?')
		return ;
	(*i)++;
	if (prompt[*i] == '?')
	{
		aux = ft_strdup(*word);
		free(*word);
		*word = NULL;
		*word = ft_strjoin(aux, ft_itoa(cmd_info->return_code));
		free(aux);
		aux = NULL;
		(*j) += ft_strlen(ft_itoa(cmd_info->return_code));
		(*i)++;
	}
	else if (ft_isdigit(prompt[*i]))
	{
		if (prompt[*i] == '0')
		{
			aux = ft_strdup(*word);
			free(*word);
			*word = NULL;
			*word = ft_strjoin(aux, "minishell");
			free(aux);
			aux = NULL;
			(*j) += ft_strlen("minishell");
			(*i)++;
		}
		(*i)++;
		return ;
	}
	else if (ft_isalpha(prompt[*i]))
	{
		k = 0;
		while (ft_isalnum(prompt[*i]))
		{
			variable = ft_realloc(variable, (ft_strlen(variable) + 1));
			variable[k] = prompt[*i];
			k++;
			variable[k] = '\0';
			(*i)++;
		}
		if (check_envi(env, variable))
		{
			aux = ft_strdup(*word);
			free(*word);
			variable = copy_expanded_env(env, variable, j);
			*word = ft_strjoin(aux, variable);
			free(aux);
		}
		else
			(*j) += ft_strlen(variable);
	}
	free(variable);
	variable = NULL;
}
