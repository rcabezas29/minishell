# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 13:43:21 by rcabezas          #+#    #+#              #
#    Updated: 2021/03/01 13:50:54 by rcabezas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = gcc -Werror -Wextra -Wall

SRCS_MS = main.c parse.c  execute.c

SRCS = $(addprefix srcs/, $(SRCS_MS))

INCLUDES_MS = minishell.h

INCLUDES = $(addprefix includes/, $(INCLUDES_MS))

OBJS = $(SRCS:.c=.o)

RM = rm -rf

LIBFT = libft

$(NAME) : $(OBJS)
	@make -C $(LIBFT)
	@$(CFLAGS) -I $(INCLUDES) $(LIBFT)/libft.a $(OBJS) -o $(NAME)

%.o: %.c
	@$(CFLAGS) -I $(INCLUDES) -o $@ -c $<

all : $(NAME)

clean :
	@$(RM) $(OBJS)
	@make clean -C $(LIBFT)

fclean : clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT)

re:				fclean all

.PHONY: 		all fclean clean re