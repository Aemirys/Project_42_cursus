/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:40:27 by estosche          #+#    #+#             */
/*   Updated: 2024/10/15 11:34:11 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_pixel(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		mlx_put_pixel(game->image, x, y, color);
	}
}

void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;

	game->pitch_offset = (int)(game->p.pitch * HEIGHT);
	y = -1;
	while (++y < HEIGHT / 2 + game->pitch_offset)
	{
		if (y >= 0 && y < HEIGHT)
		{
			x = -1;
			while (++x < WIDTH)
				set_pixel(game, x, y, game->ceiling_color);
		}
	}
	y = HEIGHT / 2 + game->pitch_offset;
	while (y < HEIGHT)
	{
		if (y >= 0 && y < HEIGHT)
		{
			x = -1;
			while (++x < WIDTH)
				set_pixel(game, x, y, game->floor_color);
		}
		y++;
	}
}

void	column(t_game *g, int x, mlx_texture_t *t, unsigned int tex_x)
{
	int	y;
	int	tex_y;
	int	color;

	y = g->start;
	while (y < g->end)
	{
		tex_y = calculate_tex_y(g, y, t);
		if (tex_y < 0)
			tex_y = 0;
		else if ((uint32_t)tex_y >= t->height)
			tex_y = t->height - 1;
		color = get_tex_co(t, tex_x, tex_y);
		if (((color >> 24) & 0xFF) != 0)
			set_pixel(g, x, y, color);
		y++;
	}
}
