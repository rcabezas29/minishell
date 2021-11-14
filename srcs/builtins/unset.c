/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:40:58 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/14 10:09:24 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*check_nums_in_unset(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_isdigit(args[i][0]))
			return (args[i]);
		i++;
	}
	return (NULL);
}

static char	**remove_env(t_env *env, char *erased)
{
	int		i;
	int		j;
	char	**newenv;

	i = 0;
	j = 0;
	i = ft_matrixlen(env->envp);
	newenv = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (env->envp[j])
	{
		if (!ft_strncmp(env->envp[j], erased, ft_strlen(erased)))
		{
			free (env->envp[j]);
			j++;
		}
		else
		{
			newenv[i++] = ft_strdup(env->envp[j++]);
			free (env->envp[j - 1]);
		}
	}
	free (env->envp);
	return (newenv);
}

static char	**save_envs(char **args)
{
	char	**ret;
	int		i;

	i = ft_matrixlen(args);
	ret = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (args[i])
	{
		ret[i] = ft_strdup(args[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

static int	check_env(char *env, char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (!ft_strncmp(env, list[i], ft_strlen(env)))
			return (1);
		i++;
	}
	return (0);
}

int	execute_unset(t_exe exe, t_env *env)
{
	int		i;
	char	**variables;
	char	*error;

	i = 0;
	error = check_nums_in_unset(exe.args);
	if (error)
	{
		printf("`%s\': not a valid identifier\n", error);
		return (1);
	}
	variables = save_envs(exe.args);
	while (variables[i + 1])
	{
		if (check_env(variables[i + 1], env->envp))
		{
			env->envp = remove_env(env, variables[i + 1]);
		}
		i++;
	}
	ft_freematrix(variables);
	return (0);
}
