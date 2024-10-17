/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:39:59 by lschweit          #+#    #+#             */
/*   Updated: 2024/10/16 10:58:59 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->p.dir_x;
	game->p.dir_x = game->p.dir_x * cos(-ROT_SPEED) \
	- game->p.dir_y * sin(-ROT_SPEED);
	game->p.dir_y = old_dir_x * sin(-ROT_SPEED) \
	+ game->p.dir_y * cos(-ROT_SPEED);
	old_plane_x = game->p.plane_x;
	game->p.plane_x = game->p.plane_x * cos(-ROT_SPEED) \
	- game->p.plane_y * sin(-ROT_SPEED);
	game->p.plane_y = old_plane_x * sin(-ROT_SPEED) \
	+ game->p.plane_y * cos(-ROT_SPEED);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->p.dir_x;
	game->p.dir_x = game->p.dir_x * cos(ROT_SPEED) \
	- game->p.dir_y * sin(ROT_SPEED);
	game->p.dir_y = old_dir_x * sin(ROT_SPEED) \
	+ game->p.dir_y * cos(ROT_SPEED);
	old_plane_x = game->p.plane_x;
	game->p.plane_x = game->p.plane_x * cos(ROT_SPEED) \
	- game->p.plane_y * sin(ROT_SPEED);
	game->p.plane_y = old_plane_x * sin(ROT_SPEED) \
	+ game->p.plane_y * cos(ROT_SPEED);
}

void	rotate_up(t_game *game)
{
	game->p.pitch += ROT_SPEED;
	if (game->p.pitch > MAX_PITCH)
		game->p.pitch = MAX_PITCH;
}

void	rotate_down(t_game *game)
{
	game->p.pitch -= ROT_SPEED;
	if (game->p.pitch < MIN_PITCH)
		game->p.pitch = MIN_PITCH;
}

void	mouse_move(double x, double y, void *param)
{
	t_game			*game;
	double			delta_x;
	double			rotation_speed;
	static double	last_x;

	(void)y;
	game = (t_game *)param;
	if (last_x == 0)
		last_x = x;
	delta_x = x - last_x;
	last_x = x;
	rotation_speed = 0.004;
	game->p.angle += delta_x * rotation_speed;
	if (game->p.angle < 0)
		game->p.angle += 2 * M_PI;
	if (game->p.angle > 2 * M_PI)
		game->p.angle -= 2 * M_PI;
	game->p.dir_x = cos(game->p.angle);
	game->p.dir_y = sin(game->p.angle);
	game->p.plane_x = game->p.dir_y * 0.66;
	game->p.plane_y = -game->p.dir_x * 0.66;
}
