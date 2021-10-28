/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:07:06 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/28 14:21:25 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <term.h>
# include <termios.h>
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
	char	*oldpwd;
	char	**paths;
}	t_env;

typedef struct s_cmd_info
{
	int		return_code;
	int		no_pipes;
	char	*file;
	t_list	*command_list;
}	t_cmd_info;

typedef struct s_node
{
	char	*prompts;
	t_type	types;
	int		built_in;
	int		comillas;
}	t_node;

typedef struct s_parser
{
	int		i;
	char	*word;
	char	*prompt;
}	t_parser;

//minishell.h
int			main(int argc, char **argv, char **envp);
void		del(void *node);
void		leaks(void);
char		*memory_main(int argc, char **argv, t_env *env, char **envp);

//environments.c
char		*ft_strchr2(const char *str, char c);
void		take_envs(char	**envp, t_env *env);
void		add_slash_to_path(t_env *env);

//find_initial_envs
int			find_initial_envs(char **envs);
int			find_oldpwd(char **envs);
int			find_pwd(char **envs);
int			find_shlvl(char **envs);

//lexer.c
void		lexer(t_env *env, t_cmd_info *cmd_info, char *prompt);
void		parse_simple_chars(t_env *env, t_parser *p,
				t_cmd_info *cmd_info, int j);
void		check_builtins(t_cmd_info *cmd_info);
void		set_next_char(t_parser *p, int *j);

//words.c
void		add_word_to_list(t_list **list, t_cmd_info *cmd_info, char *word);
void		word_analyzer(t_parser *p, t_env *env, t_cmd_info *cmd_info);

//quotes.c
void		parse_quotes(t_env *env, t_parser *p, char c, t_cmd_info *cmd_info);
void		double_quotes_after_char(t_parser *p, t_env *env,
				t_cmd_info *cmd_info, int *j);
void		simple_quotes_after_char(t_parser *p, int *j);

//execute.c
void		execute(t_cmd_info *cmd_info, t_env *env);
char		**assign_arguments_for_execve(t_list *tmp);
int			execute_paths(t_list *tmp, t_env *env);
void		ft_freearray(char **array);
int			count_arguments(t_list *tmp);
char		*cmd_path2(char *cmd, char *tmp, int check_path, t_env *env);

//execute2.c
char		*cmd_path(t_env *env, char *cmd);
void		execute_builtins(t_cmd_info *cmd_info, t_env *env);
void		analyze_prompt(t_cmd_info *cmd_info);

//builtins
void		execute_builtins(t_cmd_info *cmd_info, t_env *env);
void		execute_echo(t_cmd_info *cmd_info);
void		execute_pwd(void);
void		execute_env(t_cmd_info *cmd_info, t_env *env);
void		execute_export(t_cmd_info *cmd_info, t_env *env);
void		execute_unset(t_cmd_info *cmd_info, t_env *env);

//dolar
void		expand_dollars(t_env *env, t_parser *p,
				int *j, t_cmd_info *cmd_info);

//cd


void		execute_cd(t_cmd_info *cmd_info, t_env *env);
void		cd_alone(t_env *env);
void		cd_path(t_env *env, t_list *aux, t_cmd_info *cmd_info);
void		cd_guion(t_env *env, t_cmd_info *cmd_info);

//cd_2
void		ft_take_envs_free(t_env *env);
char		**ft_change_env(t_env *env);

//signal
void		sig_init(void);
void		sig_init2(void);

//redireccion
void		ft_indirection(t_cmd_info *cmd_info, char *entry);
void		ft_redirection(t_cmd_info *cmd_info, char *entry);
void		ft_append(t_cmd_info *cmd_info, char *entry);
void		ft_heredoc(t_cmd_info *cmd_info, char *entry);
void		ft_manageredirections(t_cmd_info *cmd_info);

//exit
void		ft_cleanmemory(t_cmd_info *cmd_info, t_env *env);
void		execute_exit(t_cmd_info *cmd_info, t_env *env);
#endif