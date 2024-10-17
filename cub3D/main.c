/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:39:16 by estosche          #+#    #+#             */
/*   Updated: 2024/10/17 13:05:50 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec + time.tv_usec / 1000000.0);
}

bool	load_game_data(char *filename, t_game *game, t_gc *gc)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (ext == NULL || ft_strcmp(ext, ".cub") != 0)
		return (printf("Error\nInvalid file extension\n"), false);
	set_dimens(filename, &game->width, &game->height, gc);
	init_textures(game);
	game->map = read_map(filename, game, gc);
	if (!game->map || is_map_valid(game) == false)
		return (false);
	size_map(game, game->map);
	find_player_position(game);
	if (!init_game(game) || init_text_ray(game) == -6)
		return (mlx_terminate(game->mlx), false);
	return (true);
}

void	cleanup_game(t_game *game, t_gc *gc)
{
	mlx_terminate(game->mlx);
	free_text_ray(game);
	gc_clean(gc);
}

int	main(int argc, char **argv)
{
	t_gc	*gc;
	t_game	*game;

	if (!init_core(argc, argv, &gc, &game))
		return (EXIT_FAILURE);
	if (!load_game_data(argv[1], game, gc))
		return (gc_clean(gc), EXIT_FAILURE);
	if (!init_mlx_hooks(game))
		return (gc_clean(gc), EXIT_FAILURE);
	mlx_loop(game->mlx);
	cleanup_game(game, gc);
	return (EXIT_SUCCESS);
}
