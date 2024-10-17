/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:43:01 by estosche          #+#    #+#             */
/*   Updated: 2024/10/16 10:43:45 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_move(mlx_key_data_t keydata, t_game *g, double m_speed)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE \
	|| keydata.action == MLX_REPEAT))
		move_forward(g, m_speed);
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE \
	|| keydata.action == MLX_REPEAT))
		move_backward(g, m_speed);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE \
	|| keydata.action == MLX_REPEAT))
		move_left_ray(g, m_speed);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE \
	|| keydata.action == MLX_REPEAT))
		move_right_ray(g, m_speed);
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE \
	|| keydata.action == MLX_REPEAT))
		rotate_left(g);
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE \
	|| keydata.action == MLX_REPEAT))
		rotate_right(g);
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_RELEASE \
	|| keydata.action == MLX_REPEAT))
		rotate_up(g);
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_RELEASE \
	|| keydata.action == MLX_REPEAT))
		rotate_down(g);
}
