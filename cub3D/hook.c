/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:29:09 by estosche          #+#    #+#             */
/*   Updated: 2024/10/16 10:30:20 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	hook_move(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	double	current_time;
	double	delta_time;
	double	move_speed;

	game = (t_game *)param;
	current_time = get_current_time();
	delta_time = current_time - game->last_time;
	game->last_time = current_time;
	move_speed = MOVE_SPEED * delta_time;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx);
	handle_move(keydata, game, move_speed);
}

void	hook_ray(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_delete_image(game->mlx, game->image);
	init_img(game);
	perform_raycasting(game);
	draw_minimap(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}

bool	init_mlx_hooks(t_game *game)
{
	mlx_key_hook(game->mlx, &hook_move, game);
	mlx_loop_hook(game->mlx, &hook_ray, game);
	mlx_cursor_hook(game->mlx, &mouse_move, game);
	if (!game->mlx)
		return (false);
	return (true);
}
