/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:26:56 by estosche          #+#    #+#             */
/*   Updated: 2024/10/15 11:45:13 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	can_move_to(t_game *game, double new_x, double new_y)
{
	double	radius;

	radius = game->p.radius;
	if (game->map[(int)(new_y + radius)][(int)(new_x + radius)] == '1' ||
	game->map[(int)(new_y - radius)][(int)(new_x + radius)] == '1' ||
	game->map[(int)(new_y + radius)][(int)(new_x - radius)] == '1' ||
	game->map[(int)(new_y - radius)][(int)(new_x - radius)] == '1')
		return (0);
	return (1);
}

void	move_forward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->p.x + game->p.dir_x * move_speed;
	new_y = game->p.y + game->p.dir_y * move_speed;
	if (can_move_to(game, new_x, new_y))
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}

void	move_backward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->p.x - game->p.dir_x * move_speed;
	new_y = game->p.y - game->p.dir_y * move_speed;
	if (can_move_to(game, new_x, new_y))
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}

void	move_right_ray(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->p.x - game->p.plane_x * move_speed;
	new_y = game->p.y - game->p.plane_y * move_speed;
	if (can_move_to(game, new_x, new_y))
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}

void	move_left_ray(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->p.x + game->p.plane_x * move_speed;
	new_y = game->p.y + game->p.plane_y * move_speed;
	if (can_move_to(game, new_x, new_y))
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}
