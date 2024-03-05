/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:22:27 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:23:46 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_last_key_event_time(t_game *game)
{	
	double	current_time;

	current_time = mlx_get_time();
	game->last_key_event_time = current_time;
}

void	check_timeout_and_reset_ismoving(t_game *game)
{
	double	current_time;
	double	timeout_threshold;

	current_time = mlx_get_time();
	timeout_threshold = 2.0;
	if (current_time - game->last_key_event_time > timeout_threshold)
		game->ismoving = false;
}

static void	hook1(mlx_key_data_t keydata, t_game *game)
{
	if (((keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
			|| (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE))
		&& (game->win == false && game->loose == false))
	{
		move_down(game);
		anim(game);
	}
	if (((keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
			|| (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE))
		&& (game->win == false && game->loose == false))
	{
		move_up(game);
		anim(game);
	}
	if (((keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
			|| (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE))
		&& (game->win == false && game->loose == false))
	{
		move_right(game);
		anim(game);
	}
}

void	hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	hook1(keydata, game);
	if (((keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
			|| (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE))
		&& (game->win == false && game->loose == false))
	{
		move_left(game);
		anim(game);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx);
	update_last_key_event_time(game);
	collectible(game);
	if (game->win == true)
		if (-1 == mlx_image_to_window(game->mlx, game->img->win, \
		(game->map_width / 2) - 187, (game->map_height / 2) - 250))
			exit((ft_printf("Error\nImage failed\n"),
					free_image(game), free_game(game), EXIT_FAILURE));
}
