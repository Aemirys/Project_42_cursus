/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:16:48 by estosche          #+#    #+#             */
/*   Updated: 2024/10/16 13:17:04 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_direction(t_game *game, char tile)
{
	if (tile == 'N')
	{
		game->p.dir_x = 0;
		game->p.dir_y = -1;
		game->p.angle = 3 * M_PI / 2;
	}
	else if (tile == 'E')
	{
		game->p.dir_x = 1;
		game->p.dir_y = 0;
		game->p.angle = 0;
	}
	else if (tile == 'S')
	{
		game->p.dir_x = 0;
		game->p.dir_y = 1;
		game->p.angle = M_PI / 2;
	}
	else if (tile == 'W')
	{
		game->p.dir_x = -1;
		game->p.dir_y = 0;
		game->p.angle = M_PI;
	}
}

void	set_player_direction(t_game *game, char tile, size_t x, size_t y)
{
	game->p.x = x + 0.5;
	game->p.y = y + 0.5;
	set_direction(game, tile);
	game->p.plane_x = game->p.dir_y * 0.66;
	game->p.plane_y = -game->p.dir_x * 0.66;
	game->map[y][x] = '0';
}

void	find_player_position(t_game *game)
{
	size_t	x;
	size_t	y;
	char	tile;

	y = -1;
	while (++y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			tile = game->map[y][x];
			if (tile == ' ' || tile == '\t')
			{
				x++;
				continue ;
			}
			if (tile == 'N' || tile == 'E' || tile == 'S' || tile == 'W')
			{
				set_player_direction(game, tile, x, y);
				return ;
			}
			x++;
		}
	}
}
