/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:56:01 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:29:32 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_print_moves(t_game *game)
{
	char	*move_count;

	game->img->mo = mlx_put_string(game->mlx, "Moves:", 10, 10);
	mlx_resize_image(game->img->mo, game->img_width, game->img_height);
	move_count = ft_itoa(game->move_count);
	mlx_delete_image(game->mlx, game->img->move_nbr);
	game->img->move_nbr = mlx_put_string(game->mlx, move_count, 100, 30);
	mlx_resize_image(game->img->\
	move_nbr, game->img_width / 2, game->img_height / 2);
	free(move_count);
}
