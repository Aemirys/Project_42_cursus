# push_swap
NAME				=	push_swap
PUSHSWAP_MAIN		=	main.c
MAIN				= $(PUSHSWAP_MAIN:.c=.o)
						
PUSHSWAP_SRC		=	stack.c stack2.c helpers.c validator.c list.c short_sort.c adv_sort.c ft_push.c \
						adv_sort2.c ft_swap.c ft_rotate.c ft_reverse_rotate.c rank.c free.c
OBJS				= $(PUSHSWAP_SRC:.c=.o)

# bonus
NAME_BONUS			=	checker
BONUS_SRC			=	checker_bonus.c $(PUSHSWAP_SRC)

OBJSBNS			= $(BONUS_SRC:.c=.o)

# Libft
LIBFT				=	./libft/libft.a

# Compiler
CC					=	cc
RM					=	rm -f
CFLAGS				=	-Wall -Werror -Wextra -g3 #-fsanitize=address


# Rules
all:		$(LIBFT) $(NAME)

bonus :		$(NAME_BONUS)

$(LIBFT):
			@make -C libft bonus

$(NAME):	$(OBJS) $(MAIN)
			$(CC) $(CFLAGS) $(OBJS) $(MAIN) $(LIBFT)  -o $(NAME)

$(NAME_BONUS):	$(OBJSBNS)
				$(CC) $(CFLAGS) $(OBJSBNS) $(LIBFT) -o $(NAME_BONUS)
			

clean:
			$(RM) $(NAME) $(OBJS) $(MAIN) $(OBJSBNS) $(NAME_BONUS)

fclean:		clean
			@make -C libft fclean

re:			fclean all

.PHONY:		libft all clean fclean bonus re
