/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:24:50 by estosche          #+#    #+#             */
/*   Updated: 2024/10/16 14:28:10 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_tile(t_game *game, t_minimap *minimap)
{
	int	i;
	int	j;

	i = 0;
	while (i < minimap->tile_size)
	{
		j = 0;
		while (j < minimap->tile_size)
		{
			if ((minimap->d_x + i >= 0 && minimap->d_x + i < WIDTH)
				&& (minimap->d_y + j >= 0 && minimap->d_y + j < HEIGHT))
			{
				mlx_put_pixel(game->image, minimap->d_x + i, \
				minimap->d_y + j, minimap->color);
			}
			j++;
		}
		i++;
	}
}

int	get_tile_color(t_game *game, char tile, t_minimap *minimap)
{
	if (minimap->x == (size_t)game->p.x && minimap->y == (size_t)game->p.y)
		return (get_tex_co(game->texture->p, 0, 0));
	else if (tile == '1')
		return (get_tex_co(game->texture->w, 0, 0));
	else if (tile == '0')
		return (get_tex_co(game->texture->f, 0, 0));
	return (0x000000);
}

void	draw_minimap(t_game *g)
{
	t_minimap	m;
	size_t		line_length;

	m.tile_size = 10;
	m.minimap_start_x = 0;
	m.minimap_start_y = 0;
	m.y = -1;
	while (++m.y < g->height)
	{
		line_length = ft_strlen(g->map[m.y]);
		m.x = -1;
		while (++m.x < line_length)
		{
			m.d_x = m.x * m.tile_size + m.minimap_start_x;
			m.d_y = m.y * m.tile_size + m.minimap_start_y;
			if (m.d_x < 0 || m.d_x >= WIDTH || m.d_y < 0 || m.d_y >= HEIGHT)
				continue ;
			if (g->map[m.y][m.x] != ' ')
			{
				m.color = get_tile_color(g, g->map[m.y][m.x], &m);
				if (m.color != 0x000000)
					draw_tile(g, &m);
			}
		}
	}
}
