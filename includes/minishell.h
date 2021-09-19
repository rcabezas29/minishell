/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:07:06 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/19 19:02:00 by rcabezas         ###   ########.fr       */
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
	char	*prompts;
	t_type	types;
}	t_node;

//minishell.h
int			main(int argc, char **argv, char **envp);

//environments.h
t_env		*take_envs(char	**envp);

//parse.c
t_list		*parse(char *prompt, t_env *env);
void		add_word_to_list(char *word, t_list **command_line);
void		ft_cmdlstadd_back(t_list *alst, t_node *new);
t_list		*ft_cmdlstlast(t_list *lst);
#endif