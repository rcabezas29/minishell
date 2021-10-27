# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fballest <fballest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 13:43:21 by rcabezas          #+#    #+#              #
#    Updated: 2021/10/27 12:15:37 by fballest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS_MS = minishell.c $(LEX_SRCS) $(ENV_SRCS) $(EXEC_SRCS) $(BUILTINS_SRCS) $(SIG_SRCS) $(REDIRECT_SRCS)

INCLUDES = includes/

SRCS_DIR = srcs/

ENV_DIR = env/

EXEC_DIR = executer/

LEX_DIR = lexer/

BUILTINS_DIR = builtins/

SIG_DIR = signals/

REDIRECT_DIR = redirections/

SRCS_LEX = lexer.c dollars.c quotes.c words.c

SRCS_EXEC = execute.c execute2.c

SRCS_ENV = environments.c find_initial_envs.c

SRCS_BUILTINS = pwd.c echo.c env.c unset.c cd.c cd_2.c export.c exit.c

SRCS_SIG = signal.c

SRCS_REDIRECT = redirections.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_MS))

ENV_SRCS = $(addprefix $(ENV_DIR), $(SRCS_ENV))

LEX_SRCS = $(addprefix $(LEX_DIR), $(SRCS_LEX))

EXEC_SRCS = $(addprefix $(EXEC_DIR), $(SRCS_EXEC))

BUILTINS_SRCS = $(addprefix $(BUILTINS_DIR), $(SRCS_BUILTINS))

SIG_SRCS = $(addprefix $(SIG_DIR), $(SRCS_SIG))

REDIRECT_SRCS = $(addprefix $(REDIRECT_DIR), $(SRCS_REDIRECT))

OBJS = $(SRCS:.c=.o)

LIBFT = libft

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g #3 -fsanitize=address

BLUE = \033[0;34m

GREEN = \033[1;32m

RESET = \033[0m

%.o: %.c
	@gcc $(CFLAGS) -I $(INCLUDES) -I/sgoinfre/students/$(USER)/homebrew/opt/readline/include -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)==========CREATING LIBFT==========$(RESET)"
	@make -C $(LIBFT)
	@echo "$(BLUE)========CREATING MINISHELL========$(RESET)"
	@gcc $(CFLAGS) -I $(INCLUDES) -lreadline -L/sgoinfre/students/$(USER)/homebrew/opt/readline/lib $(LIBFT)/libft.a $(OBJS) -o $(NAME)
	@echo "$(GREEN)=============WELLDONE=============$(RESET)"

clean:
	@echo "$(BLUE)==========CLEANING LIBFT==========$(RESET)"
	@make clean -C $(LIBFT)
	@echo "$(BLUE)====CLEANING MINISHELL OBJECTS====$(RESET)"
	@$(RM) $(OBJS)
	@echo "$(GREEN)=========CLEAN FINISHED==========$(RESET)"

fclean: clean
	@echo "$(BLUE)=====CLEANING LIBFT LIB. FILE=====$(RESET)"
	@make fclean -C $(LIBFT)
	@echo "$(BLUE)==CLEANING MINISHELL BINARY FILE==$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)=========FCLEAN FINISHED=========$(RESET)"

re:				fclean all

.PHONY: 		all fclean clean re
