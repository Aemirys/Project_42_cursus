# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estosche <estosche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 16:08:17 by estosche          #+#    #+#              #
#    Updated: 2024/03/18 09:28:48 by estosche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	pipex				
PIPEX_SRC			=	pipex.c utils.c error.c ft_split_quote.c ft_split_quote1.c
OBJS				= 	$(PIPEX_SRC:.c=.o)

# bonus
NAME_BONUS			=	pipex_bonus	
BONUS_SRC			=	pipex_bonus.c error_bonus.c utils_bonus.c utils_bonus2.c ft_split_quote_bonus.c ft_split_quote1_bonus.c
OBJSBNS				= 	$(BONUS_SRC:.c=.o)

# Libft
LIBFT				= ./libft/libft.a

# Compiler
CC					=	cc
RM					=	rm -f
CFLAGS				=	-Wall -Werror -Wextra -g3 #-fsanitize=address


# Rules
all:		$(LIBFT) $(NAME)

bonus :		$(NAME_BONUS)

$(LIBFT):
			@make -s --no-print-directory -C libft bonus

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(NAME_BONUS):	$(OBJSBNS) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJSBNS) $(LIBFT) -o $(NAME_BONUS)
			

clean:
			$(RM) $(OBJS)  $(BONUS_MAIN) $(OBJSBNS)
			@make -s --no-print-directory -C libft clean

fclean:		clean
			$(RM) $(NAME) $(NAME_BONUS)
			@make -s --no-print-directory -C libft fclean

re:			fclean all bonus

.PHONY:		libft all clean fclean bonus re

norm:
			@norminette *.c *.h