/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:01:32 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 17:18:05 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	idle_animation(t_game *game)
{
	double	frame_duration;
	int		player_x;
	int		player_y;

	player_x = game->img->player->instances->x;
	player_y = game->img->player->instances->y;
	frame_duration = 0.5;
	game->animation_timer += game->mlx->delta_time;
	while (game->animation_timer > frame_duration)
	{
		desactivate_animation_idle(game);
		if (game->frame_p != 0)
			game->img->idle[game->frame_p - 1]->instances->enabled = false;
		if (game->frame_p == 0)
			game->img->idle[3]->instances->enabled = false;
		game->img->idle[game->frame_p]->instances->enabled = true;
		game->img->idle[game->frame_p]->instances->x = player_x;
		game->img->idle[game->frame_p]->instances->y = player_y;
		game->animation_timer = 0;
		game->frame_p++;
		if (game->frame_p == 4)
			game->frame_p = 0;
	}
}

void	anim_right(t_game *game)
{
	double	frame_duration;
	int		player_x;
	int		player_y;

	player_x = game->img->player->instances->x;
	player_y = game->img->player->instances->y;
	frame_duration = 0.2;
	game->animation_timer += game->mlx->delta_time;
	if (game->animation_timer > frame_duration)
	{
		if (game->frame_p != 0)
			game->img->mr[game->frame_p - 1] \
			->instances->enabled = false;
		if (game->frame_p == 0)
			game->img->mr[3]->instances->enabled = false;
		game->img->mr[game->frame_p]->instances->enabled = true;
		game->img->mr[game->frame_p]->instances->x = player_x;
		game->img->mr[game->frame_p]->instances->y = player_y;
		game->animation_timer = 0;
		game->frame_p++;
		if (game->frame_p == 4)
			game->frame_p = 0;
	}
}

void	anim_left(t_game *game)
{
	double	frame_duration;
	int		player_x;
	int		player_y;

	player_x = game->img->player->instances->x;
	player_y = game->img->player->instances->y;
	frame_duration = 0.3;
	game->animation_timer += game->mlx->delta_time;
	if (game->animation_timer > frame_duration)
	{
		if (game->frame_p != 0)
			game->img->ml[game->frame_p - 1] \
			->instances->enabled = false;
		if (game->frame_p == 0)
			game->img->ml[3]->instances->enabled = false;
		game->img->ml[game->frame_p]->instances->enabled = true;
		game->img->ml[game->frame_p]->instances->x = player_x;
		game->img->ml[game->frame_p]->instances->y = player_y;
		game->animation_timer = 0;
		game->frame_p++;
		if (game->frame_p == 4)
			game->frame_p = 0;
	}
}

void	anim_up(t_game *game)
{
	double	frame_duration;
	int		player_x;
	int		player_y;

	player_x = game->img->player->instances->x;
	player_y = game->img->player->instances->y;
	frame_duration = 0.3;
	game->animation_timer += game->mlx->delta_time;
	if (game->animation_timer > frame_duration)
	{
		if (game->frame_p != 0)
			game->img->mu[game->frame_p - 1] \
			->instances->enabled = false;
		if (game->frame_p == 0)
			game->img->mu[3]->instances->enabled = false;
		game->img->mu[game->frame_p]->instances->enabled = true;
		game->img->mu[game->frame_p]->instances->x = player_x;
		game->img->mu[game->frame_p]->instances->y = player_y;
		game->animation_timer = 0;
		game->frame_p++;
		if (game->frame_p == 4)
			game->frame_p = 0;
	}
}

void	anim_down(t_game *game)
{
	double	frame_duration;
	int		player_x;
	int		player_y;

	player_x = game->img->player->instances->x;
	player_y = game->img->player->instances->y;
	frame_duration = 0.3;
	game->animation_timer += game->mlx->delta_time;
	if (game->animation_timer > frame_duration)
	{
		if (game->frame_p != 0)
			game->img->md[game->frame_p - 1] \
			->instances->enabled = false;
		if (game->frame_p == 0)
			game->img->md[3]->instances->enabled = false;
		game->img->md[game->frame_p]->instances->enabled = true;
		game->img->md[game->frame_p]->instances->x = player_x;
		game->img->md[game->frame_p]->instances->y = player_y;
		game->animation_timer = 0;
		game->frame_p++;
		if (game->frame_p == 4)
			game->frame_p = 0;
	}
}
