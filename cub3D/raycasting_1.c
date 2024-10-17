/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:45:31 by estosche          #+#    #+#             */
/*   Updated: 2024/10/16 10:45:34 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

mlx_texture_t	*select_tex(t_game *game, double ray_dir_x, double ray_dir_y)
{
	if (game->side == 0)
	{
		if (ray_dir_x > 0)
			return (game->texture->west);
		else
			return (game->texture->east);
	}
	else
	{
		if (ray_dir_y > 0)
			return (game->texture->north);
		else
			return (game->texture->south);
	}
}

unsigned int	calculate_tex_x(t_game *game, mlx_texture_t *texture)
{
	if (game->side == 0)
		return ((unsigned int)((game->test_y - floor(game->test_y)) \
		* texture->width));
	else
		return ((unsigned int)((game->test_x - floor(game->test_x)) \
		* texture->width));
}

unsigned int	calculate_tex_y(t_game *game, int y, mlx_texture_t *texture)
{
	int				start;
	double			wall_pos;
	unsigned int	tex_y;

	start = (HEIGHT / 2) - (game->line_height / 2) \
	+ (int)(game->p.pitch * HEIGHT);
	wall_pos = (double)(y - start) / (double)game->line_height;
	if (wall_pos < 0.0)
		wall_pos = 0.0;
	if (wall_pos > 1.0)
		wall_pos = 1.0;
	tex_y = (unsigned int)(wall_pos * texture->height);
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	return (tex_y);
}

void	draw_wall(t_game *g, int x, double ray_dir_x, double ray_dir_y)
{
	unsigned int	tex_x;
	mlx_texture_t	*texture;
	int				y;

	g->start = (HEIGHT / 2) - (g->line_height / 2) \
	+ (int)(g->p.pitch * HEIGHT);
	if (g->start < 0)
		g->start = 0;
	if (g->start >= HEIGHT)
		return ;
	g->end = g->start + g->line_height;
	if (g->end >= HEIGHT)
		g->end = HEIGHT - 1;
	y = g->start;
	while (y < g->end)
	{
		set_pixel(g, x, y, 0x000000);
		y++;
	}
	texture = select_tex(g, ray_dir_x, ray_dir_y);
	tex_x = calculate_tex_x(g, texture);
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	column(g, x, texture, tex_x);
}

bool	is_wall_at(int map_x, int map_y, char **map)
{
	if (map_x < 0 || map_y < 0 || !map[map_y] || !map[map_y][map_x])
		return (false);
	return (map[map_y][map_x] == '1');
}
