/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:07:06 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/13 15:08:10 by rcabezas         ###   ########.fr       */
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

typedef struct	s_env
{
	char	**envp;
	char	*home;
	char	*user;
	char	*pwd;
	char	**paths;
}	t_env;


//minishell.h
int		main(int argc, char **argv, char **envp);
void	define_env_variable(char *command);

//environments.h
t_env	*take_envs(char	**envp);

//parse.c
void	parse(char *prompt, t_env *env);
void	read_commands(char **commands, t_env *env);

//builtins.c
void	echo(char *command);
void	cd(char *command);
void	pwd(char *command);
void	export(char *command);
void	unset(char *command);
void	env_function(char *command);

//commands.c
void	execute_commands(char *command, t_env *env);
void	path_command(char *command, t_env *env);
void	execute(char *path, char *command, t_env *env);
#endif