/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:02:47 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:23:09 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	check_enemy(t_game *game)
{
	size_t	i;
	size_t	j;
	int		e;
	char	cell;

	i = 0;
	e = 0;
	game->enemy = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			cell = game->map[i][j];
			if (cell == 'X')
				e++;
			j++;
		}
		i++;
	}
	if (e > 1 || e == 0)
		return (ft_printf("Error\nEnemy must be one.\n"), false);
	return (true);
}

bool	is_map_valid(t_game *game)
{
	if (!is_empty(game))
		return (false);
	if (!is_rectangular(game))
		return (false);
	if (!is_enclosed_by_walls(game))
		return (false);
	if (!check_duplicates(game))
		return (false);
	if (!check_presence(game))
		return (false);
	if (!check_collectible(game))
		return (false);
	if (!check_enemy(game))
		return (false);
	return (true);
}
