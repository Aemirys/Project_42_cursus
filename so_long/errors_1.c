/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:18:43 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:27:45 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_rectangular(t_game *game)
{
	size_t	i;
	size_t	line_length;
	size_t	current_length;
	char	*first_line;
	char	*current_line;

	i = 1;
	first_line = game->map[0];
	while (*first_line != '\n' && *first_line != '\0')
		first_line++;
	line_length = first_line - game->map[0];
	while (i < game->height)
	{
		current_line = game->map[i - 1];
		game->end_line = current_line;
		while (*game->end_line != '\n' && *game->end_line != '\0')
			game->end_line++;
		current_length = game->end_line - current_line;
		if (current_length != line_length)
			return (printf("Error\nNo rectangular map.\n"), false);
		i++;
	}
	return (true);
}

bool	is_enclosed_by_walls(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->width - 1)
	{
		if (game->map[0][i] != '1')
			return (ft_printf("Error\nNot enclosed by walls.\n"), false);
		i++;
	}
	i = 1;
	while (i < game->height - 1)
	{
		if (game->map[i][0] != '1' || game->map[i][game->width - 2] != '1')
			return (printf("Error\nNot enclosed by walls.\n"), false);
		i++;
	}
	i = 0;
	while (i < game->width - 1)
	{
		if (game->map[game->height - 1][i] != '1')
			return (printf("Error\nNot enclosed by walls.\n"), false);
		i++;
	}
	return (true);
}

bool	check_presence(t_game *game)
{
	size_t	i;
	size_t	j;
	char	cell;

	i = -1;
	game->start_position = 0;
	game->exit = 0;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			cell = game->map[i][j];
			if (cell == 'P' || cell == 'E' || cell == 'X')
			{
				if (cell == 'P')
					game->start_position++;
				else if (cell == 'E')
					game->exit++;
			}
		}
	}
	if (game->start_position == 0 || game->exit == 0)
		return (ft_printf("Error\nMissing player or exit.\n"), false);
	return (true);
}

bool	check_collectible(t_game *game)
{
	size_t	i;
	size_t	j;
	char	cell;

	i = 0;
	game->collectible = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			cell = game->map[i][j];
			if (cell == 'C')
				game->collectible++;
			j++;
		}
		i++;
	}
	if (game->collectible == 0)
		return (ft_printf("Error\nMissing collectibles.\n"), false);
	return (true);
}

bool	check_duplicates(t_game *game)
{
	size_t	i;
	size_t	j;
	int		n;
	int		k;

	i = 0;
	n = 0;
	k = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'E')
				n++;
			if (game->map[i][j] == 'P')
				k++;
			j++;
		}
		i++;
	}
	if (n > 1 || k > 1)
		return (ft_printf("Error\nDuplicate found\n"), false);
	return (true);
}
