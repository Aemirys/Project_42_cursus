/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:02:47 by estosche          #+#    #+#             */
/*   Updated: 2024/10/07 14:55:51 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_empty(t_game *game)
{
	if (game->map[0])
		return (true);
	else
		return (printf("Error\nEmpty map\n"), false);
}

bool	check_presence(t_game *game)
{
	size_t	i;
	size_t	j;
	char	c;

	i = -1;
	game->start_position = 0;
	while (++i < game->height)
	{
		j = -1;
		while (++j < ft_strlen(game->map[i]))
		{
			c = game->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				game->start_position++;
		}
	}
	if (game->start_position == 0)
		return (printf("Error\nMissing player\n"), false);
	return (true);
}

bool	check_characters(t_game *game)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			c = game->map[i][j];
			if (c != '1' && c != '0' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != ' ' && c != '\t' && c != '\n')
			{
				printf("Error\nInvalid character '%c'.\n", c);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_enclosed_by_walls(t_game *game)
{
	if (!check_top_line(game))
		return (false);
	if (!check_middle_lines(game))
		return (false);
	if (!check_bottom_line(game))
		return (false);
	if (!check_characters(game))
		return (false);
	return (true);
}

bool	is_map_valid(t_game *game)
{
	if (!is_empty(game))
		return (false);
	if (!check_duplicates(game))
		return (false);
	if (!check_presence(game))
		return (false);
	if (!is_enclosed_by_walls(game))
		return (false);
	return (true);
}
