/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:54:02 by estosche          #+#    #+#             */
/*   Updated: 2024/10/17 13:04:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_ea_we_texture(char *line, t_game *game, t_gc *gc)
{
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (game->ea)
		{
			printf("Error\nDuplicate EA definition\n");
			return (-1);
		}
		game->ea = 1;
		if (load_texture_path(line, game, gc) == -5)
			return (-1);
		return (1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (game->we)
		{
			printf("Error\nDuplicate WE definition\n");
			return (-1);
		}
		game->we = 1;
		if (load_texture_path(line, game, gc) == -5)
			return (-1);
		return (1);
	}
	return (0);
}

int	handle_texture(char *line, t_game *game, t_gc *gc)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (game->no)
		{
			printf("Error\nDuplicate NO definition\n");
			return (-1);
		}
		game->no = 1;
		if (load_texture_path(line, game, gc) == -5)
			return (-1);
		return (1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (game->so)
		{
			printf("Error\nDuplicate SO definition\n");
			return (-1);
		}
		game->so = 1;
		if (load_texture_path(line, game, gc) == -5)
			return (-1);
		return (1);
	}
	return (handle_ea_we_texture(line, game, gc));
}
