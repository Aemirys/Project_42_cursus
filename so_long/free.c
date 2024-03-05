/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:18:02 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 15:44:09 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_game(t_game *game)
{
	size_t	i;

	i = 0;
	if (game->map != NULL)
	{
		while (i < game->height)
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	free(game);
}

void	free_game_temp(t_game *game)
{
	size_t	i;

	i = 0;
	if (game != NULL)
	{
		if (game->map_temp != NULL)
		{
			while (i < game->height)
			{
				free(game->map_temp[i]);
				i++;
			}
			free(game->map_temp);
		}
	}
}

void	ft_exit(t_game *game)
{
	exit((ft_printf("Error\nImage failed\n"),
			free_image(game), free_game(game), EXIT_FAILURE));
}

void	ft_exit1(t_game *game)
{
	exit((ft_printf("Error\nImage failed\n"),
			free_image1(game), free_game(game), EXIT_FAILURE));
}
