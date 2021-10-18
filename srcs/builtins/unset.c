/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:40:58 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/18 12:09:50 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	remove_env(t_env *env, char *erased)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		if (!ft_strcmp(env->envp[i], erased))
		{
			while (env->envp[i + 1])
			{
				env->envp[i] = ft_strdup(env->envp[i + 1]);
				i++;
			}
		}
		i++;
	}
	env->envp[i - 1] = NULL;
}

static char	**save_envs(t_list	*list)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) + 1);
	i = 0;
	while (list)
	{
		ret[i] = ft_strdup(((t_node *)list->content)->prompts);
		list = list->next;
		i++;
	}
	return (ret);
}

static int	check_env(char *env, char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (!ft_strncmp(env, list[i], ft_strlen(list[i])))
			return (1);
		i++;
	}
	return (0);
}

void	execute_unset(t_cmd_info *cmd_info, t_env *env)
{
	int		i;
	char	**variables;
	t_list	*tmp;

	i = 0;
	tmp = cmd_info->command_list->next;
	variables = save_envs(tmp);
	while (env->envp[i])
	{
		if (check_env(env->envp[i], variables))
			remove_env(env, env->envp[i]);
		i++;
	}
}
