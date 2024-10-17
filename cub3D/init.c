/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:18:13 by estosche          #+#    #+#             */
/*   Updated: 2024/10/16 15:50:17 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_textures(t_game *game)
{
	game->texture_paths[0] = NULL;
	game->texture_paths[1] = NULL;
	game->texture_paths[2] = NULL;
	game->texture_paths[3] = NULL;
	game->has_floor = 0;
	game->has_c = 0;
	game->no = 0;
	game->so = 0;
	game->we = 0;
	game->ea = 0;
}

int	init_text_ray(t_game *game)
{
	game->texture = ft_calloc(1, sizeof(t_textures));
	if (!game->texture)
		exit((ft_printf("Error\nFailed calloc texture\n"),
				free_text_ray(game), EXIT_FAILURE));
	game->texture->north = mlx_load_png(game->texture_paths[0]);
	game->texture->south = mlx_load_png(game->texture_paths[1]);
	game->texture->west = mlx_load_png(game->texture_paths[2]);
	game->texture->east = mlx_load_png(game->texture_paths[3]);
	game->texture->f = mlx_load_png("./png/green.png");
	game->texture->w = mlx_load_png("./png/red.png");
	game->texture->p = mlx_load_png("./png/blue.png");
	if (!game->texture->north || !game->texture->south \
	|| !game->texture->east || !game->texture->west \
	|| !game->texture->f || !game->texture->w \
	|| !game->texture->p)
		return (ft_printf("Error\nFailed to load png\n"),
			free_text_ray(game), -6);
	return (0);
}

void	init_img(t_game *game)
{
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		exit((ft_printf("Error\nFailed to initialize image\n"), EXIT_FAILURE));
}

int	init_game(t_game *game)
{
	game->pitch_offset = 0;
	game->p.pitch = 0.0;
	game->p.radius = 0.2;
	game->last_time = get_current_time();
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!(game->mlx))
		return (free(game), false);
	return (true);
}

bool	init_core(int argc, char **argv, t_gc **gc, t_game **game)
{
	(void) argv;
	*gc = gc_init();
	*game = gc_malloc(*gc, sizeof(t_game));
	if (*game == NULL)
		return (printf("Error\nAllocation memory\n"), false);
	(*game)->mini_map = gc_malloc(*gc, sizeof(t_minimap));
	if ((*game)->mini_map == NULL)
		return (printf("Error\nAllocation memory for minimap\n"), false);
	if (argc != 2)
		return (printf("Error\nInvalid number of arguments\n"), false);
	return (true);
}
