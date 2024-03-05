NAME		= so_long
SO_LONG_MAIN	= main.c
MAIN		= $(SO_LONG_MAIN:.c=.o)

SO_LONG_SRC	= map.c free.c errors.c errors_1.c errors_2.c draw.c move.c move1.c\
			items.c animation.c enemy.c status_bar.c desactivate.c load_img.c load_frames.c\
			load_frames2.c end.c

OBJS	= $(SO_LONG_SRC:.c=.o)

LIBFT	= ./libft/libft.a
LIBMLX	= ./MLX42/build/libmlx42.a

CC	= gcc
RM	= rm -f
CFLAGS	= -Wall -Werror -Wextra -g3 #-fsanitize=address
MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm

all:	$(LIBFT) $(LIBMLX) $(NAME)

$(LIBFT):
	@make -s --no-print-directory -C libft bonus

$(LIBMLX):
	@make -s --no-print-directory -C libmlx

$(NAME):	$(OBJS) $(MAIN)
				$(CC) $(CFLAGS) $(OBJS) $(MAIN) $(LIBFT) $(LIBMLX) $(MLXFLAGS)  -o $(NAME)

clean:
		$(RM) $(NAME) $(OBJS) $(MAIN)

fclean: clean
		@make --no-print-directory -C libft fclean

re:		fclean all

.PHONY:	libft libmlx all clean fclean re

norm:
	@norminette *.c *.h