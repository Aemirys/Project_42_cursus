/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:12:24 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:29:44 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    SO_LONG_H
# define    SO_LONG_H

# include "./libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

# define MAX_FRAMES 4
# define MAX_ENEMIES 10
# define WIDTH 3500
# define HEIGHT 2000

typedef struct s_textures
{
	mlx_texture_t	*floor;
	mlx_texture_t	*wall;
	mlx_texture_t	*col;
	mlx_texture_t	*player;
	mlx_texture_t	*exit;
	mlx_texture_t	*enemy;
	mlx_texture_t	*loose;
	mlx_texture_t	*win;
	mlx_texture_t	*idle[MAX_FRAMES];
	mlx_texture_t	*mr[MAX_FRAMES];
	mlx_texture_t	*ml[MAX_FRAMES];
	mlx_texture_t	*mu[MAX_FRAMES];
	mlx_texture_t	*md[MAX_FRAMES];
	mlx_texture_t	*er[MAX_FRAMES];
	mlx_texture_t	*el[MAX_FRAMES];
}				t_textures;

typedef struct s_images
{
	mlx_image_t	*move_nbr;
	mlx_image_t	*col_nbr;
	mlx_image_t	*mo;
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_image_t	*col;
	mlx_image_t	*player;
	mlx_image_t	*exit;
	mlx_image_t	*enemy;
	mlx_image_t	*loose;
	mlx_image_t	*win;
	mlx_image_t	*mr[MAX_FRAMES];
	mlx_image_t	*ml[MAX_FRAMES];
	mlx_image_t	*mu[MAX_FRAMES];
	mlx_image_t	*md[MAX_FRAMES];
	mlx_image_t	*idle[MAX_FRAMES];
	mlx_image_t	*er[MAX_FRAMES];
	mlx_image_t	*el[MAX_FRAMES];
	int			player_current_frame;
}				t_images;

typedef struct s_game
{
	int					move_delay;
	int					direction;
	bool				ismoving;
	bool				ismoving_left;
	bool				ismoving_right;
	bool				ismoving_up;
	bool				ismoving_down;
	bool				loose;
	bool				win;
	char				*end_line;
	struct s_textures	*texture;
	struct s_images		*img;
	mlx_t				*mlx;
	size_t				width;
	size_t				height;
	int					fd;
	char				**map;
	char				**map_temp;
	size_t				exit;
	size_t				collectible;
	size_t				start_position;
	size_t				enemy;
	int					frame_p;
	size_t				img_width;
	size_t				img_height;
	int					map_width;
	int					map_height;
	int					count_col;
	int					move_count;
	int					n_col;
	double				animation_timer;
	double				last_key_event_time;
	int					move_counter;
}	t_game;

//init map
t_game	*load_map(const char *filename);
void	print_map(t_game *game);
void	set_dimensions(const char *filename, size_t *width, size_t *height);
char	**read_map(char *script_map, t_game *game);
void	size_map(t_game *game, char **map);
// validation
bool	is_map_valid(t_game *game);
bool	is_rectangular(t_game *game);
bool	is_enclosed_by_walls(t_game *game);
bool	check_presence(t_game *game);
bool	check_duplicates(t_game *game);
int		valid_path(t_game *game, char *fd);
bool	is_empty(t_game *game);
bool	check_enemy(t_game *game);
bool	check_collectible(t_game *game);
// free
void	free_game(t_game *game);
void	free_game_temp(t_game *game);
void	free_img(t_game *game);
// init game
void	get_textures(t_game *game);
void	get_images(t_game *game);
void	draw_floor(t_game *game, t_images *image);
void	draw_items(t_game *game, t_images *image);
void	draw_map(t_game *game, t_images *image);
void	hook(mlx_key_data_t keydata, void *param);
//void	move_player(t_game *game);
void	check_collisions(t_game *game, int next_y, int next_x);
//items
int		count_col(t_game *game);
void	delete_col(t_game *game);
void	collectible(t_game *game);
// animation
void	draw_animation(t_game *game);
void	load_animation(t_game *game);
void	idle_animation(t_game *game);
void	get_images_frame(t_game *game);
void	get_textures_frame(t_game *game);
void	anim_right(t_game *game);
void	anim_left(t_game *game);
void	anim_down(t_game *game);
void	anim_up(t_game *game);
void	anim(void *param);
void	check_timeout_and_reset_ismoving(t_game *s_game);
void	update_last_key_event_time(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	move_up(t_game *game);
void	move_down(t_game *game);
void	desactivate_animation_move_up(t_game *game);
void	desactivate_animation_move_right(t_game *game);
void	desactivate_animation_move_down(t_game *game);
void	desactivate_animation_move_left(t_game *game);
void	desactivate_animation_idle(t_game *game);
void	get_images_frame2(t_game *game);
void	get_textures_frame2(t_game *game);
//enemy
void	move_enemy(t_game *game);
void	anim_enemy_R(t_game *game, size_t last_x, size_t last_y);
void	anim_enemy_L(t_game *game, size_t last_x, size_t last_y);
void	ft_print_moves_and_col(t_game *game);
void	ft_print_moves(t_game *game);
//verify
void	free_texture1(t_game *game);
void	free_texture2(t_game *game);
void	free_texture3(t_game *game);
void	verify_image1(t_game *game);
void	verify_load1(t_game *game);
void	verify_load2(t_game *game);
void	free_image(t_game *game);
void	free_image1(t_game *game);

void	ft_end(t_game *game);
void	ft_exit(t_game *game);
void	ft_exit1(t_game *game);

#endif
