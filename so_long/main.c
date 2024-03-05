/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:25:11 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:31:23 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	anim(void *param)
{
	t_game	*game;

	game = param;
	if (game->ismoving == false)
		idle_animation(game);
	else
	{
		if (game->ismoving_right)
			anim_right(game);
		else if (game->ismoving_left)
			anim_left(game);
		else if (game->ismoving_up)
			anim_up(game);
		else if (game->ismoving_down)
			anim_down(game);
	}
	check_timeout_and_reset_ismoving(game);
	mlx_key_hook(game->mlx, &hook, game);
	ft_end(game);
}

void	enemy(void *param)
{
	t_game	*game;

	game = param;
	if (game->loose == false)
		move_enemy(game);
	else if (game->loose == true)
	{
		if (-1 == mlx_image_to_window(game->mlx, game->img->loose, \
		(game->map_width / 2) - 144, (game->map_height / 2) - 180))
			exit((ft_printf("Error\nImage failed\n"),
					free_image(game), free_game(game), EXIT_FAILURE));
	}
}

void	init(t_game *game)
{
	game->move_count = 0;
	game->count_col = 0;
	game->ismoving = false;
	game->ismoving_left = false;
	game->ismoving_right = false;
	game->ismoving_up = false;
	game->ismoving_down = false;
	game->frame_p = 0;
	game->last_key_event_time = 0;
	game->loose = false;
	game->direction = 1;
	game->move_counter = 0;
	game->win = false;
	game->move_delay = 20;
}

int	init_game(t_game *game)
{
	init(game);
	game->mlx = mlx_init(game->map_width, game->map_height, "so_long", true);
	if (!(game->mlx))
		return (free(game), false);
	get_textures(game);
	get_images(game);
	get_textures_frame(game);
	get_textures_frame2(game);
	get_images_frame(game);
	draw_map(game, game->img);
	draw_animation(game);
	mlx_loop_hook(game->mlx, &anim, game);
	mlx_loop_hook(game->mlx, &enemy, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free(game->texture);
	free(game->img);
	return (true);
}

int	main(int argc, char **argv)
{
	t_game	*game;
	char	*filename;

	game = malloc(sizeof(t_game));
	if (game == NULL)
		return (ft_printf("Error allocating memory for game"), free(game), 0);
	if (argc != 2)
		return (ft_printf("Error\nInvalid arguments\n"), free(game), 0);
	filename = ft_strrchr(argv[1], '.');
	if (filename == NULL || ft_strcmp(filename, ".ber") != 0)
		return (ft_printf("Error\nInvalid file extension.\n"), free(game), 0);
	game->map = read_map(argv[1], game);
	if (!game->map)
		return ((free(game), EXIT_FAILURE));
	if (is_map_valid(game) == false)
		return (free_game(game), EXIT_FAILURE);
	if (valid_path(game, argv[1]) == false)
		return (free(game), EXIT_FAILURE);
	size_map(game, game->map);
	if (init_game(game) == false)
		return (free_game(game), EXIT_FAILURE);
	return (free_game(game), EXIT_SUCCESS);
}
