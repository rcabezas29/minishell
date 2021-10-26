/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:15:28 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/26 16:21:34 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_arguments(t_list *tmp)
{
	t_list	*aux;
	int		i;

	aux = tmp;
	i = 0;
	while (((t_node *)aux) && ((t_node *)aux->content)->types == ARGUMENT)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

char	**assign_arguments_for_execve(t_list *tmp)
{
	char	**ret;
	int		i;
	int		narg;

	narg = count_arguments(tmp);
	ret = NULL;
	ret = (char **)malloc(sizeof(char *) * (narg + 1));
	i = 0;
	while (i < narg)
	{
		ret[i] = ft_strdup(((t_node *)tmp->content)->prompts);
		tmp = tmp->next;
		i++;
		ret[i] = NULL;
	}
	return (ret);
}

// static void	sig_int_son(int sig)
// {
// 	if (sig == SIGINT || sig == SIGQUIT)
// 		exit (0);
// }

int	execute_paths(t_list *tmp, t_env *env)
{
	char			*path;
	int				pid;
	char			**exeggutor;
	int				j;
	int				ret;

	j = 0;
	path = cmd_path(env, (char *)((t_node *)tmp->content)->prompts);
	exeggutor = assign_arguments_for_execve(tmp);
	pid = fork();
	if (pid == 0)
	{
		// signal(SIGINT, sig_int_son);
		// signal(SIGQUIT, sig_int_son);
		ret = execve(path, exeggutor, env->envp);
		exit(ret);
	}
	else
	{
		waitpid(pid, &j, 0);
		free(path);
		path = NULL;
		ft_freematrix(exeggutor);
	}
	return (j % 255);
}

void	execute(t_cmd_info *cmd_info, t_env *env)
{
	int				i;
	t_list			*tmp;
	struct termios	old;

	i = 0;
	tmp = cmd_info->command_list;
	tcgetattr(0, &old);
	while (i <= cmd_info->no_pipes)
	{
		if (((t_node *)tmp->content)->types == 0)
		{
			if (((t_node *)tmp->content)->built_in == 1)
				execute_builtins(cmd_info, env);
			else
			{
				cmd_info->return_code = execute_paths(tmp, env);
				break ;
			}
		}
		i++;
	}
	tcsetattr(0, TCSANOW, &old);
}

char	*cmd_path2(char *cmd, char *tmp, int check_path, t_env *env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	if (open(cmd, O_RDONLY) >= 0)
		return (cmd);
	while (env->paths[i])
	{
		tmp = ft_strjoin(env->paths[i], cmd);
		check_path = open(tmp, O_RDONLY);
		if (check_path < 0)
		{
			free(tmp);
			i++;
		}
		else
		{
			path = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
			break ;
		}
	}
	return (path);
}
