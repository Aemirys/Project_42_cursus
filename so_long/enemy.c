/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:54:56 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:26:49 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_enemy(t_game *game)
{
	game->move_counter++;
	if (game->move_counter >= game->move_delay)
	{
		if (game->direction == 1)
		{
			if (game->map[game->img->enemy->instances->y / game->img_height] \
			[game->img->enemy->instances->x / game->img_width + 1] != '1')
				game->img->enemy->instances->x += game->img_width;
			else
				game->direction = -1;
		}
		if (game->direction == -1)
		{
			if (game->map[game->img->enemy->instances->y / game->img_height] \
			[game->img->enemy->instances->x / game->img_width - 1] != '1')
				game->img->enemy->instances->x -= game->img_width;
			else
				game->direction = 1;
		}
		game->move_counter = 0;
	}
	if (game->img->enemy->instances->x == game->img->player->instances->x && \
	game->img->enemy->instances->y == game->img->player->instances->y)
		game->loose = true;
}
