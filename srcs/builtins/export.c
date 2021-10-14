/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:39:38 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/14 21:13:18 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		double_ptr_len(char	**arr)
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
	ret = malloc(sizeof(*ret) * (double_ptr_len(arr) + 1));
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
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
	
	ordered = order_envs(envs);
	i = 0;
	while (ordered[i])
	{
		printf("%s\n", ordered[i]);
		i++;
	}
}

void		execute_export(t_cmd_info *cmd_info, t_env *env)
{
	if (count_arguments(cmd_info->command_list) == 1)
	{
		print_envs_export(env->envp);
		return ;
	}
}