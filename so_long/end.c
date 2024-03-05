/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:49:24 by estosche          #+#    #+#             */
/*   Updated: 2024/02/29 16:50:53 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_end(t_game *game)
{
	if (game->win == true)
	{
		desactivate_animation_move_up(game);
		desactivate_animation_move_down(game);
		desactivate_animation_idle(game);
		desactivate_animation_move_left(game);
		desactivate_animation_move_right(game);
	}
	if (game->loose == true)
	{
		desactivate_animation_move_up(game);
		desactivate_animation_move_down(game);
		desactivate_animation_idle(game);
		desactivate_animation_move_left(game);
		desactivate_animation_move_right(game);
	}
}
