# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estosche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 12:59:04 by estosche          #+#    #+#              #
#    Updated: 2023/11/02 16:33:57 by estosche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
#CFLAGS = -Wall -Werror -Wextra
SRCS = 	ft_printf.c ft_char.c ft_integer.c ft_putchar.c ft_string.c\
		ft_pointer.c ft_unsigned.c ft_hexa.c

OBJ = $(SRCS:.c=.o)

.c.o:
	$(CC)  -I . -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
