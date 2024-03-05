/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_frames2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:56:30 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:28:56 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_texture2(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game->texture->idle[i])
			mlx_delete_texture(game->texture->idle[i]);
		if (game->texture->mr[i])
			mlx_delete_texture(game->texture->mr[i]);
		if (game->texture->ml[i])
			mlx_delete_texture(game->texture->ml[i]);
		if (game->texture->mu[i])
			mlx_delete_texture(game->texture->mu[i]);
		if (game->texture->md[i])
			mlx_delete_texture(game->texture->md[i]);
	}
}

void	verify_load1(t_game *game)
{
	if (!game->texture->idle[0] || !game->texture->idle[1]
		|| !game->texture->idle[2] || !game->texture->idle[3]
		|| !game->texture->mr[0] || !game->texture->mr[1]
		|| !game->texture->mr[2] || !game->texture->mr[3]
		|| !game->texture->ml[0] || !game->texture->ml[1]
		|| !game->texture->ml[2] || !game->texture->ml[3])
		exit((ft_printf("Error\nFailed to load3 png\n"),
				free_texture2(game), EXIT_FAILURE));
}

void	verify_load2(t_game *game)
{
	if (!game->texture->mu[0] || !game->texture->mu[1]
		|| !game->texture->mu[2] || !game->texture->mu[3]
		|| !game->texture->md[0] || !game->texture->md[1]
		|| !game->texture->md[2] || !game->texture->md[3])
		exit((ft_printf("Error\nFailed to load4 png\n"),
				free_texture2(game), EXIT_FAILURE));
}

void	free_image1(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game->img->idle[i])
			mlx_delete_image(game->mlx, game->img->idle[i]);
		if (game->img->mr[i])
			mlx_delete_image(game->mlx, game->img->mr[i]);
		if (game->img->ml[i])
			mlx_delete_image(game->mlx, game->img->ml[i]);
		if (game->img->mu[i])
			mlx_delete_image(game->mlx, game->img->mu[i]);
		if (game->img->md[i])
			mlx_delete_image(game->mlx, game->img->md[i]);
	}
}

void	verify_image1(t_game *game)
{
	if (!game->img->idle[0] || !game->img->idle[1]
		|| !game->img->idle[2] || !game->img->idle[3]
		|| !game->img->mr[0] || !game->img->mr[1]
		|| !game->img->mr[2] || !game->img->mr[3]
		|| !game->img->ml[0] || !game->img->ml[1]
		|| !game->img->ml[2] || !game->img->ml[3]
		|| !game->img->mu[0] || !game->img->mu[1]
		|| !game->img->mu[2] || !game->img->mu[3]
		|| !game->img->md[0] || !game->img->md[1]
		|| !game->img->md[2] || !game->img->md[3])
		exit((ft_printf("Error\nFailed to load5 png\n"),
				free_texture2(game), free_image1(game), EXIT_FAILURE));
}
