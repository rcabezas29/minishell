# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/09 09:36:16 by rcabezas          #+#    #+#              #
#    Updated: 2021/02/26 11:45:24 by rcabezas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = 	compute.c ft_printf.c init.c nbrutils.c parse.c parsesizes.c \
		printchar.c printnegsign.c printpercent.c printptr.c printsign.c \
		printstr.c printuns.c sizes_ast.c utils.c

OBJS = ${SRCS:.c=.o}

INCLUDES = ../../includes

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rc $(NAME) $(OBJS)
	@ranlib $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -I $(INCLUDES) -o $@ -c $<

clean:
	@$(RM) $(OBJS)

fclean:     clean
	@$(RM) $(NAME)

re:		fclean all