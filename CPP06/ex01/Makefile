NAME				=	Serializer
SRCS				=	main.cpp Serializer.cpp
OBJS				= 	$(SRCS:.cpp=.o)

# Compiler
CC					=	@c++
RM					=	@rm -f
CFLAGS				+=	-Wall -Werror -Wextra -std=c++98

DEF_COLOR = \033[0;39m
PURPLE = \033[38;5;125m
CANDY = \033[38;5;205m
PINK = \033[38;5;225m

# Rules
all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "$(PINK)Make done$(DEF_COLOR)"

%.o: %.cpp
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM) $(OBJS)
			@echo "$(PURPLE)Clean done$(DEF_COLOR)"

fclean:		clean
			@$(RM) $(NAME)
			@echo "$(CANDY)fclean done$(DEF_COLOR)"

re:			fclean all 

.PHONY:		all clean fclean re