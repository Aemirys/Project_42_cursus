# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estosche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 11:31:22 by estosche          #+#    #+#              #
#    Updated: 2023/10/31 11:33:02 by estosche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	ft_printf.c ft_char.c ft_integer.c ft_putchar.c ft_string.c\
	ft_pointer.c ft_unsigned.c ft_hexa.c get_next_line.c newline_found.c

SRCSB = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
	ft_lstmap.c

OBJ = $(SRCS:.c=.o)

OBJB = $(SRCSB:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -I . -c $< -o $(<:.c=.o)
all: $(NAME)
	

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	ranlib $(NAME)

bonus: $(NAME) $(OBJB)
	@ar rcs $(NAME) $(OBJB)
	ranlib $(NAME)

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME) $(OBJB)

re: fclean all

.PHONY: all bonus clean fclean re 
