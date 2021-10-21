/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:39:24 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/21 13:33:24 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	**order_envs(char **envs)
{
	char	**ordered;
	char	*tmp;
	int		i;
	int		j;

	ordered = ft_matrixdup(envs);
	i = 0;
	while (i < ft_matrixlen(envs))
	{
		j = 1;
		while (ordered[j])
		{
			if (ft_strcmp(ordered[j - 1], ordered[j]) > 0)
			{
				tmp = ordered[j - 1];
				ordered[j - 1] = ordered[j];
				ordered[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (ordered);
}

void	print_envs_export(char **envs)
{
	int		i;
	char	**ordered;
	char	*name;
	char	*value;

	ordered = order_envs(envs);
	i = 0;
	while (ordered[i])
	{
		name = ft_strtok(ordered[i], '=');
		value = ft_strchr2(ordered[i], '=');
		if (value)
			printf("%s=\"%s\"\n", name, value);
		else
			printf("%s=\"\"\n", name);
		free (name);
		i++;
	}
	ft_freematrix(ordered);
}

char	**add_string_to_array(char **arr, char *str)
{
	char	**ret;
	char	*name;
	char	*aux;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_matrixlen(arr) + 2));
	while (arr[i])
	{
		aux = ft_strtok(arr[i], '=');
		name = ft_strjoin(aux, "=");
		if (!ft_strncmp(name, str, ft_strlen(name)) && ft_strchr(str, '='))
			ret[i] = ft_strdup(str);
		else
			ret[i] = ft_strdup(arr[i]);
		ret[++i] = NULL;
		free(name);
		free(aux);
	}
	if (!check_env(str, ret))
		ret[i++] = ft_strdup(str);
	ret[i] = NULL;
	ft_freematrix(arr);
	arr = NULL;
	return (ret);
}

void	execute_export(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*tmp;

	if (count_arguments(cmd_info->command_list) == 1)
	{
		print_envs_export(env->envp);
		return ;
	}
	tmp = cmd_info->command_list->next;
	while (tmp)
	{
		env->envp = add_string_to_array(env->envp,
				((t_node *)tmp->content)->prompts);
		tmp = tmp->next;
	}
}
