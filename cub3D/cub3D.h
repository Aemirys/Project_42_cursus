/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:47:32 by estosche          #+#    #+#             */
/*   Updated: 2024/10/17 13:03:51 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# include <math.h>
# include <time.h>
# include <sys/time.h>

# define WIDTH 1900
# define HEIGHT 1000
# define ROT_SPEED 0.05
# define MAX_BLOCKS 1024
# define MOVE_SPEED 1.5
# define MAX_PITCH 0.5
# define MIN_PITCH -0.5

typedef struct s_MemoryBlock
{
	void	*ptr;
	size_t	size;
	int		is_use;
}				t_MemoryBlock;

typedef struct s_gc
{
	t_MemoryBlock	blocks[MAX_BLOCKS];
	size_t			block_count;
}				t_gc;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	pitch;
	double	radius;
	double	angle;
}						t_player;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*f;
	mlx_texture_t	*w;
	mlx_texture_t	*p;
}				t_textures;

typedef struct s_minimap
{
	int		tile_size;
	int		minimap_start_x;
	int		minimap_start_y;
	size_t	x;
	size_t	y;
	int		d_x;
	int		d_y;
	int		color;
}				t_minimap;

typedef struct s_rgba
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				t_rgba;

typedef struct s_game
{
	int			has_floor;
	int			has_c;
	int			no;
	int			so;
	int			ea;
	int			we;
	t_minimap	*mini_map;
	int			pitch_offset;
	int			start;
	int			side;
	int			line_height;
	double		perp_wall_dist;
	double		test_x;
	double		test_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		step_x;
	double		step_y;
	int			end;
	int			floor_color;
	int			ceiling_color;
	t_player	p;
	mlx_image_t	*image;
	char		*texture_paths[4];
	t_textures	*texture;
	mlx_t		*mlx;
	size_t		width;
	size_t		height;
	int			fd;
	char		**map;
	size_t		start_position;
	size_t		img_width;
	size_t		img_height;
	size_t		map_width;
	size_t		map_height;
	double		last_time;
}				t_game;

// draw
void			set_pixel(t_game *game, int x, int y, int color);
void			draw_floor_and_ceiling(t_game *game);
void			column(t_game *g, int x, mlx_texture_t *t, unsigned int tex_x);

//errors_1
void			count_ns(t_game *game, int *n, int *s);
void			count_ew(t_game *game, int *e, int *w);
bool			check_duplicates(t_game *game);

//errors_2
bool			check_top_line(t_game *game);
bool			check_bottom_line(t_game *game);
bool			check_walls(t_game *game, size_t i);
bool			check_internal_chars(t_game *game, size_t i);
bool			check_middle_lines(t_game *game);

//errors
bool			is_empty(t_game *game);
bool			check_presence(t_game *game);
bool			check_characters(t_game *game);
bool			is_enclosed_by_walls(t_game *game);
bool			is_map_valid(t_game *game);

// garbage
t_gc			*gc_init(void);
void			*gc_malloc(t_gc *gc, size_t size);
void			gc_free(t_gc *gc, void *ptr);
void			gc_clean(t_gc *gc);

// hook
void			hook_move(mlx_key_data_t keydata, void *param);
void			hook_ray(void *param);
bool			init_mlx_hooks(t_game *game);

//init
void			init_textures(t_game *game);
int				init_text_ray(t_game *game);
void			init_img(t_game *game);
int				init_game(t_game *game);
bool			init_core(int argc, char **argv, t_gc **gc, t_game **game);

//main
double			get_current_time(void);

//map_1
int				is_ignored_line(char *line);
char			**read_map_data(int fd, t_game *game, t_gc *gc, char *line);
int				handle_colors(char *line, t_game *game);
int				load_texture_path(char *line, t_game *game, t_gc *gc);

// map_2
int				handle_texture(char *line, t_game *game, t_gc *gc);

///map_dimension
bool			ignore_line(const char *line);
void			update_dim(const char *line, size_t *curr_w, size_t *h);
void			size_map(t_game *game, char **map);
void			set_dimens(const char *file, size_t *w, size_t *h, t_gc *gc);

//map
char			**read_map(char *script_map, t_game *game, t_gc *gc);

// minimap
void			draw_tile(t_game *game, t_minimap *minimap);
int				get_tile_color(t_game *game, char tile, t_minimap *minimap);
void			draw_minimap(t_game *g);

// moves_1
void			handle_move(mlx_key_data_t keydata, t_game *g, double m_speed);

//moves
int				can_move_to(t_game *game, double new_x, double new_y);
void			move_forward(t_game *game, double move_speed);
void			move_backward(t_game *game, double move_speed);
void			move_right_ray(t_game *game, double move_speed);
void			move_left_ray(t_game *game, double move_speed);

// parse_color
void			skip_spaces(char **line);
bool			parse_component(char **line, int *component);
bool			validate_end(char *line);
int				parse_color(char *line);

// player_position
void			find_player_position(t_game *game);

// raycasting_1
mlx_texture_t	*select_tex(t_game *game, double ray_dir_x, double ray_dir_y);
unsigned int	calculate_tex_x(t_game *game, mlx_texture_t *texture);
unsigned int	calculate_tex_y(t_game *game, int y, mlx_texture_t *texture);
void			draw_wall(t_game *g, int x, double ray_dir_x, double ray_dir_y);
bool			is_wall_at(int map_x, int map_y, char **map);

//raycasting
unsigned int	get_tex_co(mlx_texture_t *text, unsigned int x, unsigned int y);
void			initialize_ray(t_game *g, double ray_dir_x, double ray_dir_y);
void			update_ray(t_game *g, double dist_x, double dist_y, int *hit);
int				cast_ray(t_game *game, double ray_dir_x, double ray_dir_y);
void			perform_raycasting(t_game *game);

//rotate
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
void			rotate_up(t_game *game);
void			rotate_down(t_game *game);
void			mouse_move(double x, double y, void *param);

//utils
char			*gc_strdup(t_gc *gc, char *s);
void			free_text_ray(t_game *game);
void			free_game(t_game *game);
void			clean_gnl_buffer(int fd);

#endif