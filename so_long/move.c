/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:58:38 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 17:20:18 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_game *game)
{
	int	player_x;
	int	player_y;
	int	i;

	i = -1;
	player_x = game->img->player->instances->x;
	player_y = game->img->player->instances->y;
	desactivate_animation_move_up(game);
	if (game->map[player_y / game->img_height - 1] \
	[player_x / game->img_width] != '1')
	{
		game->img->player->instances->y -= game->img_height;
		game->move_count++;
		ft_print_moves(game);
		ft_printf("MOVES: %i\n", game->move_count);
		if (game->frame_p == 2 || game->frame_p == 3 || \
		game->frame_p == 0 || game->frame_p == 1)
		{
			while (++i < 4)
				game->img->mu[i]->instances->y -= game->img_height;
		}
		game->ismoving = true;
		game->ismoving_down = false;
		game->ismoving_up = true;
	}
}

void	move_right(t_game *game)
{
	int	player_x;
	int	player_y;
	int	i;

	i = -1;
	player_x = game->img->player->instances->x;
	player_y = game->img->player->instances->y;
	desactivate_animation_move_right(game);
	if (game->map[player_y / game->img_height] \
	[player_x / game->img_width + 1] != '1')
	{
		game->img->player->instances->x += game->img_width;
		game->move_count++;
		ft_print_moves(game);
		ft_printf("MOVES: %i\n", game->move_count);
		if (game->frame_p == 2 || game->frame_p == 3 || \
		game->frame_p == 0 || game->frame_p == 1)
		{
			while (++i < 4)
				game->img->mr[i]->instances->x += game->img_width;
		}
		game->ismoving = true;
		game->ismoving_left = false;
		game->ismoving_right = true;
	}
}

void	move_down(t_game *game)
{
	int	player_x;
	int	player_y;
	int	i;

	player_x = game->img->player->instances->x;
	player_y = game->img->player->instances->y;
	i = -1;
	desactivate_animation_move_down(game);
	if (game->map[player_y / game->img_height + 1] \
	[player_x / game->img_width] != '1')
	{
		game->img->player->instances->y += game->img_width;
		game->move_count++;
		ft_print_moves(game);
		ft_printf("MOVES: %i\n", game->move_count);
		if (game->frame_p == 2 || game->frame_p == 3 || \
		game->frame_p == 0 || game->frame_p == 1)
			while (++i < 4)
				game->img->md[i]->instances->y += game->img_width;
		game->ismoving = true;
		game->ismoving_left = false;
		game->ismoving_right = false;
		game->ismoving_down = true;
		game->ismoving_up = false;
	}
}

void	move_left(t_game *game)
{
	int	player_x;
	int	player_y;
	int	i;

	player_x = game->img->player->instances->x;
	player_y = game->img->player->instances->y;
	i = -1;
	if (game->map[player_y / game->img_height] \
	[player_x / game->img_width - 1] != '1')
	{
		desactivate_animation_move_left(game);
		game->img->player->instances->x -= game->img_width;
		game->move_count++;
		ft_print_moves(game);
		ft_printf("MOVES: %i\n", game->move_count);
		if (game->frame_p == 2 || game->frame_p == 3 || \
		game->frame_p == 0 || game->frame_p == 1)
		{
			while (++i < 4)
				game->img->ml[i]->instances->x -= game->img_width;
		}
		game->ismoving = true;
		game->ismoving_left = true;
		game->ismoving_right = false;
	}
}
