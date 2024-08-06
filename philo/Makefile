# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estosche <estosche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 10:28:17 by estosche          #+#    #+#              #
#    Updated: 2024/08/06 15:01:21 by estosche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo				
PHILO_SRC			=	main.c init.c thread.c launch.c utils.c utils_libft.c
OBJS				= 	$(PHILO_SRC:.c=.o)


# Compiler
CC					=	@cc
RM					=	@rm -f
CFLAGS				=	-Wall -Werror -Wextra -g3 -fsanitize=thread #-fsanitize=address -fsanitize=leak  

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
all:		 $(NAME)


$(NAME):	$(OBJS) 
			
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "$(MAGENTA)Make done$(DEF_COLOR)"

clean:
			$(RM) $(OBJS)
			@echo "$(CYAN)Clean done$(DEF_COLOR)"

fclean:		clean
			$(RM) $(NAME)
			@echo "$(GREEN)fclean done$(DEF_COLOR)"

re:			fclean all 

.PHONY:		all clean fclean bonus re

norm:
			@norminette *.c *.h