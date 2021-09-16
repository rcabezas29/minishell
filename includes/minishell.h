/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:07:06 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/16 10:23:19 by fballest         ###   ########.fr       */
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
	APPEND
}			t_type;

typedef struct s_env
{
	char	**envp;
	char	*home;
	char	*user;
	char	*pwd;
	char	**paths;
}	t_env;

typedef struct s_node
{
	char	*content;
	t_type	type;
}	t_node;

typedef struct s_cmd_list
{
	t_node				*content;
	struct s_cmd_list	*next;
}	t_cmd_list;

//minishell.h
int			main(int argc, char **argv, char **envp);

//environments.h
t_env		*take_envs(char	**envp);

//parse.c
t_cmd_list	*parse(char *prompt, t_env *env);
void		add_word_to_list(char *word, t_cmd_list *command_line);
void		ft_cmdlstadd_back(t_cmd_list *alst, t_node *new);
t_cmd_list	*ft_cmdlstlast(t_cmd_list *lst);
#endif