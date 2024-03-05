/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:38:03 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:26:34 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_floor(t_game *game, t_images *image)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width - 1)
		{
			if (-1 == mlx_image_to_window(game->mlx, image->floor, \
			x * game->img_width, y * game->img_height))
				ft_exit(game);
			x++;
		}
		y++;
	}
}

void	draw_items(t_game *game, t_images *image)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->map[y][x] == '1')
				if (-1 == mlx_image_to_window(game->mlx, image->wall,
						x * game->img_width, y * game->img_height))
					ft_exit(game);
			if (game->map[y][x] == 'C')
				if (-1 == mlx_image_to_window(game->mlx, image->col,
						x * game->img_width, y * game->img_height))
					ft_exit(game);
			if (game->map[y][x] == 'E')
				if (-1 == mlx_image_to_window(game->mlx, image->exit,
						x * game->img_width, y * game->img_height))
					ft_exit(game);
		}
	}
}

void	draw_map(t_game *game, t_images *image)
{
	size_t	x;
	size_t	y;

	draw_floor(game, image);
	draw_items(game, image);
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'X')
				if (-1 == mlx_image_to_window(game->mlx, image->enemy,
						x * game->img_width, y * game->img_height))
					ft_exit(game);
			if (game->map[y][x] == 'P' && game->loose == false)
				if (-1 == mlx_image_to_window(game->mlx, image->player,
						x * game->img_width, y * game->img_height))
					ft_exit(game);
			x++;
		}
		y++;
	}
}

static void	ft_instances(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		game->img->idle[i]->instances->enabled = false;
		game->img->mr[i]->instances->enabled = false;
		game->img->ml[i]->instances->enabled = false;
		game->img->mu[i]->instances->enabled = false;
		game->img->md[i]->instances->enabled = false;
	}
	game->img->player->instances->enabled = false;
}

void	draw_animation(t_game *game)
{
	int	p_x;
	int	p_y;
	int	i;

	p_x = game->img->player->instances->x;
	p_y = game->img->player->instances->y;
	i = -1;
	while (++i < 4)
	{
		if (-1 == mlx_image_to_window(game->mlx, game->img->idle[i], p_x, p_y))
			ft_exit1(game);
		if (-1 == mlx_image_to_window(game->mlx, game->img->mr[i], p_x, p_y))
			ft_exit1(game);
		if (-1 == mlx_image_to_window(game->mlx, game->img->ml[i], p_x, p_y))
			ft_exit1(game);
		if (-1 == mlx_image_to_window(game->mlx, game->img->mu[i], p_x, p_y))
			ft_exit1(game);
		if (-1 == mlx_image_to_window(game->mlx, game->img->md[i], p_x, p_y))
			ft_exit1(game);
	}
	ft_instances(game);
}
