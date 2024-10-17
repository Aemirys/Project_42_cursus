/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:36:31 by estosche          #+#    #+#             */
/*   Updated: 2024/09/25 10:55:27 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_top_line(t_game *game)
{
	size_t	i;

	i = 0;
	while (game->map[0][i] != '\0' && game->map[0][i] != '\n')
	{
		while (game->map[0][i] == '\t' || game->map[0][i] == ' ')
			i++;
		if (game->map[0][i] != '1' && game->map[0][i] != '\n')
		{
			printf("Error\nNot enclosed by walls.\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_bottom_line(t_game *game)
{
	size_t	i;

	i = 0;
	while (game->map[game->height - 1][i] != '\0')
	{
		if (game->map[game->height - 1][i] == '\t'
			|| game->map[game->height - 1][i] == ' ')
		{
			i++;
			continue ;
		}
		if (game->map[game->height - 1][i] != '1'
			&& game->map[game->height - 1][i] != '\n')
		{
			printf("Error\nNot enclosed by walls.\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_walls(t_game *game, size_t i)
{
	size_t	j;

	j = 0;
	while (game->map[i][j] == '\t' || game->map[i][j] == ' ')
		j++;
	if (game->map[i][j] != '1')
	{
		printf("Error\nNot enclosed by walls.\n");
		return (false);
	}
	j++;
	while (game->map[i][j] != '\0')
		j++;
	j--;
	while (j > 0 && (game->map[i][j] == '\t'
		|| game->map[i][j] == ' ' || game->map[i][j] == '\n'))
		j--;
	if (game->map[i][j] != '1')
	{
		printf("Error\nNot enclosed by walls.\n");
		return (false);
	}
	return (true);
}

bool	check_internal_chars(t_game *game, size_t i)
{
	size_t	j;
	char	c;

	j = 1;
	while (game->map[i][j] != '\0')
	{
		c = game->map[i][j];
		if (c == '0')
		{
			if (game->map[i][j - 1] == ' ' || game->map[i][j - 1] == '\t' \
			|| game->map[i][j - 1] == '\n' || game->map[i][j - 1] == '\0' \
			|| game->map[i][j + 1] == ' ' || game->map[i][j + 1] == '\t' \
			|| game->map[i][j + 1] == '\n' || game->map[i][j + 1] == '\0' \
			|| game->map[i - 1][j] == ' ' || game->map[i - 1][j] == '\t' \
			|| game->map[i - 1][j] == '\n' || game->map[i - 1][j] == '\0' \
			|| game->map[i + 1][j] == ' ' || game->map[i + 1][j] == '\t' \
			|| game->map[i + 1][j] == '\n' || game->map[i + 1][j] == '\0')
			{
				printf("Error\nNot enclosed by walls.\n");
				return (false);
			}
		}
		j++;
	}
	return (true);
}

bool	check_middle_lines(t_game *game)
{
	size_t	i;

	i = 1;
	while (i < game->height - 1)
	{
		if (!check_walls(game, i))
		{
			return (false);
		}
		if (!check_internal_chars(game, i))
		{
			return (false);
		}
		i++;
	}
	return (true);
}
