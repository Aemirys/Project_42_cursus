# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estosche <estosche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 10:01:38 by estosche          #+#    #+#              #
#    Updated: 2024/10/17 13:03:02 by estosche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	cub3D	
CUB3D_SRC			=	main.c garbage.c map.c map_1.c map_dimension.c errors.c errors_1.c errors_2.c \
						utils.c init.c draw.c minimap.c raycasting.c moves.c rotate.c parse_color.c \
						raycasting_1.c moves_1.c hook.c player_position.c map_2.c
						
						 
OBJS				= 	$(CUB3D_SRC:.c=.o)

# Libft
LIBFT				= ./libft/libft.a

#MLX42
LIBMLX				= ./MLX42/build/libmlx42.a

# Compiler
CC					=	@cc
RM					=	@rm -f
CFLAGS				=	-Wall -Werror -Wextra -g3 #-fsanitize=leak -fsanitize=address
MLXFLAGS			=	-Iinclude -ldl -lglfw -pthread -lm

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
all:		$(LIBFT)  $(LIBMLX) $(NAME) 


$(LIBFT):
			@make -s --no-print-directory -C libft bonus

$(LIBMLX):
			@make -s --no-print-directory -C libmlx

$(NAME):	$(OBJS) $(LIBFT)
			@make -s --no-print-directory -C libft
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBMLX) $(MLXFLAGS) -o $(NAME)
			@echo "$(MAGENTA)Make done$(DEF_COLOR)"

clean:
			$(RM) $(OBJS)
			@make -s --no-print-directory -C libft clean
			@echo "$(CYAN)Clean done$(DEF_COLOR)"

fclean:		clean
			$(RM) $(NAME)
			@make -s --no-print-directory -C libft fclean
			@echo "$(GREEN)Fclean done$(DEF_COLOR)"

re:			fclean all 

.PHONY:		libft libmlx all clean fclean bonus re 

norm:
			@norminette *.c *.h || true