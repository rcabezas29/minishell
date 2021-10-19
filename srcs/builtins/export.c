/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:39:38 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/19 22:03:46 by rcabezas         ###   ########.fr       */
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

void	print_envs_export(char	**envs)
{
	int		i;
	char	**ordered;
	char	**split;

	ordered = order_envs(envs);
	i = 0;
	while (ordered[i])
	{
		split = ft_split(ordered[i], '=');
		printf("%s", split[0]);
		if (split[1])
			printf("=\"%s\"", split[1]);
		else
			printf("=\"\"");
		printf("\n");
		ft_freematrix(split);
		i++;
	}
	ft_freematrix(ordered);
}

char	**add_string_to_array(char **arr, char *str)
{
	char	**ret;
	char	**split;
	int		i;

	ret = malloc(sizeof(char *) * (ft_matrixlen(arr) + 2));
	i = 0;
	while (arr[i])
	{
		split = ft_split(arr[i], '=');
		if (!ft_strncmp(split[0], str, ft_strlen(split[0]))
			&& ft_strchr(str, '='))
			ret[i] = ft_strdup(str);
		else
			ret[i] = ft_strdup(arr[i]);
		ft_freematrix(split);
		i++;
		ret[i] = NULL;
	}
	if (!check_env(str, ret))
	{
		ret[i] = ft_strdup(str);
		i++;
	}
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
