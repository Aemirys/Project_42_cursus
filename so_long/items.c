/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:39:03 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:28:26 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_col(t_game *game)
{
	int		total;
	size_t	i;
	size_t	j;
	char	cell;

	total = 0;
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			cell = game->map[i][j];
			if (cell == 'C')
				total++;
			j++;
		}
		i++;
	}
	return (total);
}

void	delete_col(t_game *game)
{
	int		i;
	int		count;
	size_t	col_x;
	size_t	col_y;

	i = 0;
	count = game->n_col;
	while (i < count)
	{
		col_x = game->img->col->instances[i].x / game->img_width;
		col_y = game->img->col->instances[i].y / game->img_height;
		if ((size_t)game->img->player->instances->x / game->img_width == col_x
			&& (size_t)game->img->player->instances->y / game->\
			img_height == col_y
			&& game->img->col->instances[i].enabled == true)
		{
			count--;
			game->img->col->instances[i].enabled = false;
			return ;
		}
		i++;
	}
}

void	collectible(t_game *game)
{
	if (game->map[game->img->player->instances->y / game->img_height]
		[game->img->player->instances->x / game->img_width] == 'C')
	{
		delete_col(game);
		game->map[game->img->player->instances->y / game->img_height] \
		[game->img->player->instances->x / game->img_width] = '0';
		game->count_col++;
	}
	if (game->map[game->img->player->instances->y / game->img_height]
		[game->img->player->instances->x / game->img_width] == 'E')
	{
		if (game->count_col == game->n_col)
		{
			game->win = true;
			ft_printf("Congrats: YOU WIN!!");
		}
	}
}
