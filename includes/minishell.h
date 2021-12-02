/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:07:06 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/02 18:40:59 by rcabezas         ###   ########.fr       */
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

# define READ_END 0
# define WRITE_END 1

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

typedef struct s_exe
{
	int		fd_in;
	char	*cmd;
	char	**args;
	int		fd_out;
}	t_exe;

typedef struct s_cmd_info
{
	int		return_code;
	int		no_pipes;
	char	*line;
	t_list	*command_list;
	t_exe	*exe;
}	t_cmd_info;

typedef struct s_node
{
	char	*prompts;
	t_type	types;
	int		comillas;
	int		fd_in;
	int		fd_out;
}	t_node;

typedef struct s_parser
{
	int		i;
	char	*word;
	char	*prompt;
}	t_parser;

/*
** MINISHELL.C
** OJO BORRAR LEAKS Y PRINT_LIST
*/
void		leaks(void);
void		print_list(t_cmd_info *cmd_info);
void		del(void *node);
char		*memory_main(int argc, char **argv);
int			main(int argc, char **argv, char **envp);

/*
** ENV/ENVIROMENTS.C
*/
char		*ft_strchr2(const char *str, char c);
char		**add_basic_envs(char **envp);
void		take_envs(char	**envp, t_env *env);
void		add_slash_to_path(t_env *env);

/*
** ENV/FIND_INITIAL_ENVS.C
*/
int			find_initial_envs(char **envs);
int			find_oldpwd(char **envs);
int			find_pwd(char **envs);
int			find_shlvl(char **envs);

/*
** LEXER/LEXER.C
*/
void		set_next_char(t_parser *p, int *j);
int			check_dollar_to_print(t_parser *p);
int			parse_simple_chars(t_env *env, t_parser *p,
				t_cmd_info *cmd_info, int j);
void		lexer(t_env *env, t_cmd_info *cmd_info, char *prompt);

/*
** LEXER/WORDS.C
*/
void		word_analyzer(t_parser *p, t_env *env, t_cmd_info *cmd_info);
void		add_word_to_list(t_list **list, t_cmd_info *cmd_info, char *word,
				int comillas);

/*
** LEXER/QUOTES.C
*/
void		parse_quotes(t_env *env, t_parser *p, char c, t_cmd_info *cmd_info);
void		simple_quotes_after_char(t_parser *p, int *j);
void		double_quotes_after_char(t_parser *p, t_env *env,
				t_cmd_info *cmd_info, int *j);

/*
** LEXER/DOLLAR.C
** Also include this static funtions:
** static char	*copy_expanded_env(t_env *env, char *variable, int *j);
** static int	check_envi(t_env *env, char *variable);
*/
void		dollar_variables(t_parser *p, t_env *env, int *j);
void		expand_dollar_digit(t_parser *p, int *j);
void		expand_dollars(t_env *env, t_parser *p,
				int *j, t_cmd_info *cmd_info);

/*
** EXECUTER/EXECUTE.C
*/
int			count_arguments(t_list *tmp);
char		**assign_arguments_for_execve(t_list *tmp);
int			execute_paths(t_list *tmp, t_env *env);
void		execute(t_cmd_info *cmd_info, t_env *env);
char		*cmd_path2(char *cmd, char *tmp, int check_path, t_env *env);

/*
** EXECUTER/EXECUTE2.C
*/
char		*cmd_path(t_env *env, char *cmd);
int			execute_builtins(t_exe exe, t_env *env);

/*
** BUILTINS/CD.C
*/
int			cd_alone(t_env *env);
int			cd_guion(t_env *env);
int			cd_path(t_env *env, t_exe exe);
int			execute_cd(t_exe exe, t_env *env);

/*
** BUILTINS/CD_2.C
*/
void		ft_take_envs_free(t_env *env);
void		ft_change_env(t_env *env);

/*
** BUILTINS/ECHO.C
*/
void		print_after_know_flag(int n, t_exe exe, int jump);
int			flag_to_one(t_list **tmp);
int			execute_echo(t_exe exe);

/*
** BUILTINS/ENV.C
*/
int			execute_env(t_exe exe, t_env *env);

/*
** BUILTINS/EXIT.C
*/
int			alpha_in_string(char *str);
void		alpha_exit(char *alpha);
void		normal_exit(char *n);
int			execute_exit(t_exe exe);

/*
** BUILTINS/EXPORT.C
** Also include this static funtion:
** static int	check_env(char *env, char **list);
*/
char		**order_envs(char **envs);
void		print_envs_export(char **envs);
char		**add_string_to_array(char **arr, char *str);
int			execute_export(t_exe exe, t_env *env);

/*
** BUILTINS/PWD.C
*/
int			execute_pwd(void);

/*
** BUILTINS/UNSET.C
** Also include this static funtions:
** static char	*check_nums_in_unset(t_list *list);
** static char	**remove_env(t_env *env, char *erased);
** static char	**save_envs(t_list	*list);
** static int	check_env(char *env, char **list);
*/
int			execute_unset(t_exe exe, t_env *env);

/*
** BUILTINS/BUILTIN_UTILS.C
*/
char		**remove_env(t_env *env, char *erased);
void		ft_change_env(t_env *env);
void		ft_take_envs_free(t_env *env);

/*
** SIGNAL/SIGNAL.C
** Also include this static funtions:
** static void	sig_int(int sig);
** static void	sig_quit(int sig);
*/
void		child_signal(void);
void		sig_init(void);
void		cancel_signals(void);
void		sig_int(int sig);
void		sig_quit(int sig);
void		not_sig_quit(int sig);
void		not_sig_int(int sig);

/*
** REDIRECTIONS/REDIRECTION.C
** Also include this static funtions:
** static void	ft_heredoc_buc(char *file, int fd);
*/
char		*fill_env(char *dollar, t_env *env);
int			ft_heredoc(char *file, t_cmd_info *cmd_info, t_env *env,
				int comillas);
void		ft_heredoc_bucle(const char *file, t_env *env, int comillas,
				int fd);
char		*heredoc_expander(const char *file, char *tmp, t_env *env);
char		*fill_env(char *dollar, t_env *env);
int			ft_indirection(char *filename, t_cmd_info *cmd_info);
int			ft_redirection(char *filename, t_cmd_info *cmd_info);
void		ft_manageredirections(t_cmd_info *cmd_info, t_env *env);

/*
** PARSER/PARSER.C
*/
void		parser(t_cmd_info *cmd_info);

/*
** PARSER/PREPARSER.C
*/
char		*expand_mayorminor(char *prompt, int *i, int *j);
int			check_end_prompt(char *prompt, t_cmd_info *cmd_info);
char		*check_prompt(char *prompt, t_cmd_info *cmd_info);

/*
** PARSER/ANALYZER.C
*/
void		analyze_prompt(t_cmd_info *cmd_info, t_env *env);

/*
** PARSER/ASSIGN_EXE.C
*/
void		assign_arguments_from_list(t_list *tmp, t_exe *exe, int n);
void		assign_cmd_from_argument(t_cmd_info *cmd_info, t_list *tmp,
				int *arg, int i);
void		assign_fd_from_list(t_list *tmp, t_exe *exe, int n);

/*
** EXECUTER/SIMPLE_COMMANDS.C
*/
int			execute_simple_commands(t_cmd_info *cmd_info, t_env *env);
char		**assign_arguments_with_cmd(t_exe exe);
int			check_builtin(char *cmd);

/*
** EXECUTER/MANAGE_FDS.C
*/
void		restore_fds(int saved_stdin, int saved_stdout);
void		manage_fds(t_exe exe, int *fd_stdin, int *fd_stdout);

/*
** EXECUTER/PIPES.C
*/
int			execute_pipes(t_cmd_info *cmd_info, t_env *env);


void		change_shlvl(t_env *env);
#endif
