/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:13:46 by estosche          #+#    #+#             */
/*   Updated: 2024/10/02 12:53:09 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	count_ns(t_game *game, int *n, int *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'N')
				(*n)++;
			if (game->map[i][j] == 'S')
				(*s)++;
			j++;
		}
		i++;
	}
}

void	count_ew(t_game *game, int *e, int *w)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'E')
				(*e)++;
			if (game->map[i][j] == 'W')
				(*w)++;
			j++;
		}
		i++;
	}
}

bool	check_duplicates(t_game *game)
{
	int	n;
	int	s;
	int	e;
	int	w;

	n = 0;
	s = 0;
	e = 0;
	w = 0;
	count_ns(game, &n, &s);
	count_ew(game, &e, &w);
	if (n > 1 || s > 1 || e > 1 || w > 1)
		return (printf("Error\nDuplicate found\n"), false);
	if ((n + s + e + w) > 1)
		return (printf("Error\nMore than one player character found\n"), false);
	return (true);
}
