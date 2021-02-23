# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 13:43:21 by rcabezas          #+#    #+#              #
#    Updated: 2021/02/23 14:05:17 by rcabezas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = gcc -Werror -Wextra -Wall

SRCS = 

INCLUDES = includes/minishell.h

OBJS = $(SRCS:.c=.o)

RM = rm -rf

LIBFT = libft

$(NAME) : $(OBJS)
	@make -C $(LIBFT)
	@$(CFLAGS) -I $(INCLUDES) $(LIBFT)/libft.a $(OBJS) -o $(NAME)

%.o: %.c
	@$(CFLAGS) -I $(INCLUDES) -o $@ -c $<

clean :
	@$(RM) $(OBJS)
	@make clean -C $(LIBFT)

fclean : clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT)

re:				fclean all

.PHONY: 		all fclean clean re