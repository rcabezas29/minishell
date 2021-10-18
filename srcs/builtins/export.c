/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:39:38 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/18 12:09:31 by fballest         ###   ########.fr       */
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

int		double_ptr_len(char	**arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char			**double_ptr_dup(char **arr)
{
	int		i;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * (double_ptr_len(arr) + 1));
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
		ret[i] = NULL;
	}
	return (ret);
}

char	**order_envs(char **envs)
{
	char	**ordered;
	char	*tmp;
	int		i;
	int		j;

	ordered = double_ptr_dup(envs);
	i  = 0;
	while (i < double_ptr_len(envs))
	{
		j = 1;
		while (ordered[j])
		{
			if (ft_strcmp(ordered[j - 1], ordered[j]) > 0)
			{
				tmp = ft_strdup(ordered[j - 1]);
				ordered[j - 1] = ft_strdup(ordered[j]);
				ordered[j] = ft_strdup(tmp);
				free(tmp);
			}
			j++;
		}
		i++;
	}
	return (ordered);
}

void		print_envs_export(char	**envs)
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
		free_double_ptr(split);
		i++;
	}
}

char	**add_string_to_array(char **arr, char *str)
{
	char	**ret;
	char	**split;
	int		i;

	ret = malloc(sizeof(char *) * (double_ptr_len(arr) + 2));
	i = 0;
	while (arr[i])
	{
		split = ft_split(arr[i], '=');
		if (!ft_strncmp(split[0], str, ft_strlen(split[0])) && ft_strchr(str, '='))
			ret[i] = ft_strdup(str);
		else
			ret[i] = ft_strdup(arr[i]);
		free_double_ptr(split);
		i++;
		ret[i] = NULL;
	}
	if (!check_env(str, ret))
	{
		ret[i] = ft_strdup(str);
		i++;
	}
	ret[i] = NULL;
	free_double_ptr(arr);
	arr = NULL;
	return (ret);
}

void		execute_export(t_cmd_info *cmd_info, t_env *env)
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
		env->envp = add_string_to_array(env->envp, ((t_node *)tmp->content)->prompts);
		tmp = tmp->next;
	}
}
