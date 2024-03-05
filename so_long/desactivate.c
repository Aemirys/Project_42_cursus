/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desactivate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:08:32 by estosche          #+#    #+#             */
/*   Updated: 2024/02/29 16:43:44 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	desactivate_animation_move_up(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		game->img->idle[i]->instances->enabled = false;
		game->img->mr[i]->instances->enabled = false;
		game->img->ml[i]->instances->enabled = false;
		game->img->md[i]->instances->enabled = false;
	}
}

void	desactivate_animation_move_right(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		game->img->idle[i]->instances->enabled = false;
		game->img->ml[i]->instances->enabled = false;
		game->img->md[i]->instances->enabled = false;
		game->img->mu[i]->instances->enabled = false;
	}
}

void	desactivate_animation_move_left(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		game->img->idle[i]->instances->enabled = false;
		game->img->mr[i]->instances->enabled = false;
		game->img->mu[i]->instances->enabled = false;
		game->img->md[i]->instances->enabled = false;
	}
}

void	desactivate_animation_move_down(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		game->img->idle[i]->instances->enabled = false;
		game->img->mr[i]->instances->enabled = false;
		game->img->ml[i]->instances->enabled = false;
		game->img->mu[i]->instances->enabled = false;
	}
}

void	desactivate_animation_idle(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		game->img->mr[i]->instances->enabled = false;
		game->img->ml[i]->instances->enabled = false;
		game->img->md[i]->instances->enabled = false;
		game->img->mu[i]->instances->enabled = false;
	}
}
