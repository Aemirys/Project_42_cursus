# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estosche <estosche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 10:28:17 by estosche          #+#    #+#              #
#    Updated: 2024/08/01 13:05:15 by estosche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell				
MINISHELL_SRC		=	lexer.c lexer2.c main.c parser.c parser_1.c parser_2.c parser_3.c execute.c \
						parser_4.c parser_5.c ft_split_quote.c ft_split_quote1.c history.c signals.c \
						execute_1.c execute_2.c error.c builtins.c free.c free_1.c\
						prompt.c free_2.c free_3.c env.c builtin_unset.c execute_3.c\
						builtin_cd.c builtin_echo.c builtin_exit.c \
						builtin_export_1.c builtin_export_2.c builtin_export_3.c \
						builtin_export_4.c utils.c utils_2.c init.c execute_builtins.c \
						signals_heredoc.c heredoc_1.c heredoc_2.c execute_utils.c \
						redir_1.c redir_2.c redir_3.c execute_first_1.c execute_first_2.c execute_middle.c \
						execute_last.c execute_single_1.c execute_single_2.c execute_single_3.c \
						
						 
OBJS				= 	$(MINISHELL_SRC:.c=.o)

# Libft
LIBFT				= ./libft/libft.a

# Compiler
CC					=	@cc
RM					=	@rm -f
CFLAGS				=	-Wall -Werror -Wextra -g3 #-fsanitize=leak -fsanitize=address

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Rules
all:		$(LIBFT) $(NAME)


$(LIBFT):
			@make -s --no-print-directory -C libft bonus

$(NAME):	$(OBJS) $(LIBFT)
			@make -s --no-print-directory -C libft
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline #-ltermios
			@echo "$(MAGENTA)Make done$(DEF_COLOR)"

clean:
			$(RM) $(OBJS)
			@make -s --no-print-directory -C libft clean
			@echo "$(CYAN)Clean done$(DEF_COLOR)"

fclean:		clean
			$(RM) $(NAME)
			@make -s --no-print-directory -C libft fclean
			@echo "$(GREEN)fclean done$(DEF_COLOR)"

re:			fclean all 

.PHONY:		libft all clean fclean bonus re

norm:
			@norminette *.c *.h