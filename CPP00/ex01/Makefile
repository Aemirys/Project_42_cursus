# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estosche <estosche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 11:42:43 by emy               #+#    #+#              #
#    Updated: 2024/10/29 10:39:47 by estosche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	PhoneBook
SRC					=	Main.cpp Contact.cpp PhoneBook.cpp  
OBJS				= 	$(SRC:.cpp=.o)

# Compiler
CC					=	@c++
RM					=	@rm -f
CFLAGS				=	-Wall -Werror -Wextra -std=c++98

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
all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "$(MAGENTA)Make done$(DEF_COLOR)"

%.o: %.cpp
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM) $(OBJS)
			@echo "$(CYAN)Clean done$(DEF_COLOR)"

fclean:		clean
			@$(RM) $(NAME)
			@echo "$(GREEN)fclean done$(DEF_COLOR)"

re:			fclean all 

.PHONY:		all clean fclean re