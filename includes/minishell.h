/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:07:06 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/23 13:12:49 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"

typedef enum s_type
{
	ARGUMENT,
	PIPE,
	INDIRECTION,
	REDIRECTION,
	HERE_DOC,
	APPEND,
	FILE_NAME
}			t_type;

typedef struct s_env
{
	char	**envp;
	char	*home;
	char	*user;
	char	*pwd;
	char	**paths;
}	t_env;

typedef struct s_cmd_info
{
	int		no_pipes;
	t_list	*command_list;
}	t_cmd_info;

typedef struct s_node
{
	char	*prompts;
	t_type	types;
	int		built_in;
}	t_node;

//minishell.h
int			main(int argc, char **argv, char **envp);

//environments.h
t_env		*take_envs(char	**envp);
void		add_slash_to_path(t_env *env);

//parse.c
t_list		*parse(t_cmd_info *cmd_info, char *prompt);
void		add_word_to_list(t_cmd_info *cmd_info, char *word);
void		analyze_prompt(t_cmd_info *cmd_info);
void		check_builtins(t_node *node);

//execute.c
void		execute(t_cmd_info *cmd_info, t_env *env);
char		*cmd_path(t_env *env, char *cmd);
char		**assign_arguments_for_execve(t_list *tmp);
void		execute_paths(t_list *tmp, t_env *env);
void		ft_freearray(char **array);
#endif