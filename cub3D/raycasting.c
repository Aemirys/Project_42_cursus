/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:38:15 by emy               #+#    #+#             */
/*   Updated: 2024/10/15 11:44:54 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	get_tex_co(mlx_texture_t *text, unsigned int x, unsigned int y)
{
	unsigned char	*pixels;
	unsigned int	color;
	unsigned int	index;
	t_rgba			rgba;	

	pixels = (unsigned char *)text->pixels;
	if (x >= text->width || y >= text->height)
		return (0);
	index = (y * text->width + x) * 4;
	rgba.r = pixels[index];
	rgba.g = pixels[index + 1];
	rgba.b = pixels[index + 2];
	rgba.a = pixels[index + 3];
	color = (rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | rgba.a;
	return (color);
}

void	initialize_ray(t_game *g, double ray_dir_x, double ray_dir_y)
{
	g->map_x = (int)g->p.x;
	g->map_y = (int)g->p.y;
	if (ray_dir_x < 0)
	{
		g->step_x = -1;
		g->side_dist_x = (g->p.x - g->map_x) * fabs(1 / ray_dir_x);
	}
	else
	{
		g->step_x = 1;
		g->side_dist_x = (g->map_x + 1.0 - g->p.x) * fabs(1 / ray_dir_x);
	}
	if (ray_dir_y < 0)
	{
		g->step_y = -1;
		g->side_dist_y = (g->p.y - g->map_y) * fabs(1 / ray_dir_y);
	}
	else
	{
		g->step_y = 1;
		g->side_dist_y = (g->map_y + 1.0 - g->p.y) * fabs(1 / ray_dir_y);
	}
}

void	update_ray(t_game *g, double dist_x, double dist_y, int *hit)
{
	if (g->side_dist_x < g->side_dist_y)
	{
		g->side_dist_x += dist_x;
		g->map_x += g->step_x;
		g->side = 0;
	}
	else
	{
		g->side_dist_y += dist_y;
		g->map_y += g->step_y;
		g->side = 1;
	}
	if (is_wall_at(g->map_x, g->map_y, g->map))
		*hit = 1;
}

int	cast_ray(t_game *game, double ray_dir_x, double ray_dir_y)
{
	double	delta_dist_x;
	double	delta_dist_y;
	int		hit;

	hit = 0;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	game->map_x = (int)game->p.x;
	game->map_y = (int)game->p.y;
	initialize_ray(game, ray_dir_x, ray_dir_y);
	while (hit == 0)
	{
		update_ray(game, delta_dist_x, delta_dist_y, &hit);
	}
	if (game->side == 0)
		game->perp_wall_dist = (game->map_x - game->p.x \
		+ (1 - game->step_x) / 2) / ray_dir_x;
	else
		game->perp_wall_dist = (game->map_y - game->p.y \
		+ (1 - game->step_y) / 2) / ray_dir_y;
	if (game->perp_wall_dist < 0.1)
		return (-1);
	game->test_x = game->p.x + ray_dir_x * game->perp_wall_dist;
	game->test_y = game->p.y + ray_dir_y * game->perp_wall_dist;
	return (game->side);
}

void	perform_raycasting(t_game *game)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	x = 0;
	draw_floor_and_ceiling(game);
	while (x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		ray_dir_x = game->p.dir_x - game->p.plane_x * camera_x;
		ray_dir_y = game->p.dir_y - game->p.plane_y * camera_x;
		game->side = cast_ray(game, ray_dir_x, ray_dir_y);
		if (game->perp_wall_dist > 0)
			game->line_height = (int)(HEIGHT / game->perp_wall_dist);
		else
			game->line_height = HEIGHT;
		draw_wall(game, x, ray_dir_x, ray_dir_y);
		x++;
	}
}
