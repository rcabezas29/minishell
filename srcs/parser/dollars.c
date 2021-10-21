/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:42:46 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/21 12:03:02 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*copy_expanded_env(t_env *env, char *variable, int *j)
{
	int		i;
	char	*ret;
	char	*var;

	i = 0;
	ret = NULL;
	while (env->envp[i])
	{
		var = ft_strtok(env->envp[i], '=');
		if (!ft_strcmp(var, variable))
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
	int		i;
	char	*var;

	i = 0;
	while (env->envp[i])
	{
		var = ft_strtok(env->envp[i], '=');
		if (!ft_strcmp(var, variable))
			return (1);
		i++;
	}
	return (0);
}

void	expand_dollars(t_env *env, t_parser *p, int *j, t_cmd_info *cmd_info)
{
	char	*variable;
	int		k;

	variable = malloc(sizeof(char));
	if (!ft_isalnum(p->prompt[p->i + 1]) && p->prompt[p->i + 1] != '?' && p->prompt[p->i + 1] != '_')
		return ;
	p->i++;
	if (p->prompt[p->i] == '?')
	{
		p->word = ft_itoa(cmd_info->return_code);
		(*j) += ft_strlen(ft_itoa(cmd_info->return_code));
		p->i++;
	}
	else if (ft_isdigit(p->prompt[p->i]))
	{
		if (p->prompt[p->i] == '0')
		{
			p->word = ft_strdup("minishell");
			(*j) += ft_strlen("minishell");
			p->i++;
		}
		p->i++;
		return ;
	}
	else if (ft_isalpha(p->prompt[p->i]) || p->prompt[p->i] == '_')
	{
		k = 0;
		while (ft_isalnum(p->prompt[p->i]) || p->prompt[p->i] == '_')
		{
			variable = ft_realloc(variable, (ft_strlen(variable) + 1));
			variable[k] = p->prompt[p->i];
			k++;
			variable[k] = '\0';
			p->i++;
		}
		if (check_envi(env, variable))
		{
			variable = copy_expanded_env(env, variable, j);
			p->word = ft_strjoin(p->word, variable);
		}
	}
	free(variable);
	variable = NULL;
}
