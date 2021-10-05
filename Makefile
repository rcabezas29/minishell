# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fballest <fballest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 13:43:21 by rcabezas          #+#    #+#              #
#    Updated: 2021/10/05 10:26:24 by fballest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS_MS = minishell.c $(PARSER_SRCS) $(ENV_SRCS) $(EXEC_SRCS) $(BUILTINS_SRCS)

INCLUDES = includes/

SRCS_DIR = srcs/

ENV_DIR = env/

EXEC_DIR = executer/

PARSER_DIR = parser/

BUILTINS_DIR = builtins/

SRCS_PARSER = parse.c

SRCS_EXEC = execute.c

SRCS_ENV = environments.c

SRCS_BUILTINS = pwd.c #cd.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_MS))

ENV_SRCS = $(addprefix $(ENV_DIR), $(SRCS_ENV))

PARSER_SRCS = $(addprefix $(PARSER_DIR), $(SRCS_PARSER))

EXEC_SRCS = $(addprefix $(EXEC_DIR), $(SRCS_EXEC))

BUILTINS_SRCS = $(addprefix $(BUILTINS_DIR), $(SRCS_BUILTINS))

OBJS = $(SRCS:.c=.o)

LIBFT = libft

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g #3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@gcc $(CFLAGS) -I $(INCLUDES) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib $(LIBFT)/libft.a $(OBJS) -o $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -I $(INCLUDES) -I/Users/$(USER)/.brew/opt/readline/include -o $@ -c $<

clean:
	@make clean -C $(LIBFT)
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT)
	@$(RM) $(NAME)

re:				fclean all

.PHONY: 		all fclean clean re
