/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:08:34 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:28:07 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_empty(t_game *game)
{
	if (game->map[0])
		return (true);
	else
		return (ft_printf("Error\nEmpty map\n"), false);
}

static int	*start_pos(char **map)
{
	int	x;
	int	y;
	int	*pos;

	pos = (int *)ft_calloc(2, sizeof(int));
	if (pos == NULL)
		exit ((free(*map), EXIT_FAILURE));
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'P')
			{
				pos[0] = y;
				pos[1] = x;
				return (pos);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

static void	flood_map(t_game *game, size_t y, size_t x)
{
	if (!(x < 1 || y < 1 || x >= game->width || y > game->height
			|| game->map_temp[y][x] == '1' || game->map_temp[y][x] == 'X'))
	{
		game->map_temp[y][x] = 'X';
		flood_map(game, y + 1, x);
		flood_map(game, y - 1, x);
		flood_map(game, y, x + 1);
		flood_map(game, y, x - 1);
	}
}

static int	check_flood(char **map, size_t height, size_t width)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width - 1)
		{
			if (map[i][j] != '1' && map[i][j] != 'X' && map[i][j] != '0')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	valid_path(t_game *game, char *fd)
{
	int		*pos;
	size_t	height;
	size_t	width;

	game->map_temp = read_map(fd, game);
	pos = start_pos(game->map_temp);
	flood_map(game, pos[0], pos[1]);
	set_dimensions(fd, &width, &height);
	if (check_flood(game->map_temp, height, width) == false)
	{
		free(pos);
		free_game_temp(game);
		return (ft_printf("Error\nNo valid path.\n"), false);
	}
	free(pos);
	free_game_temp(game);
	return (true);
}
