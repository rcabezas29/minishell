# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 13:43:21 by rcabezas          #+#    #+#              #
#    Updated: 2021/09/22 19:32:02 by rcabezas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS_MS = minishell.c $(PARSER_SRCS) $(ENV_SRCS) $(EXEC_SRCS)

INCLUDES = includes/

SRCS_DIR = srcs/

ENV_DIR = env/

EXEC_DIR = executer/

PARSER_DIR = parser/

SRCS_PARSER = parse.c

SRCS_EXEC = execute.c

SRCS_ENV = environments.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_MS))

ENV_SRCS = $(addprefix $(ENV_DIR), $(SRCS_ENV))

PARSER_SRCS = $(addprefix $(PARSER_DIR), $(SRCS_PARSER))

EXEC_SRCS = $(addprefix $(EXEC_DIR), $(SRCS_EXEC))

OBJS = $(SRCS:.c=.o)

LIBFT = libft

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

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
