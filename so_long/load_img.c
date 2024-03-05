/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:34:19 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:30:02 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_texture1(t_game *game)
{
	if (game->texture->floor)
		mlx_delete_texture(game->texture->floor);
	if (game->texture->wall)
		mlx_delete_texture(game->texture->wall);
	if (game->texture->col)
		mlx_delete_texture(game->texture->col);
	if (game->texture->player)
		mlx_delete_texture(game->texture->player);
	if (game->texture->exit)
		mlx_delete_texture(game->texture->exit);
	if (game->texture->enemy)
		mlx_delete_texture(game->texture->enemy);
	if (game->texture->win)
		mlx_delete_texture(game->texture->win);
	if (game->texture->loose)
		mlx_delete_texture(game->texture->loose);
}

void	free_image(t_game *game)
{
	if (game->img->floor)
		mlx_delete_image(game->mlx, game->img->floor);
	if (game->img->wall)
		mlx_delete_image(game->mlx, game->img->wall);
	if (game->img->col)
		mlx_delete_image(game->mlx, game->img->col);
	if (game->img->player)
		mlx_delete_image(game->mlx, game->img->player);
	if (game->img->exit)
		mlx_delete_image(game->mlx, game->img->exit);
	if (game->img->enemy)
		mlx_delete_image(game->mlx, game->img->enemy);
	if (game->img->win)
		mlx_delete_image(game->mlx, game->img->win);
	if (game->img->loose)
		mlx_delete_image(game->mlx, game->img->loose);
}

void	get_textures(t_game *game)
{
	game->texture = ft_calloc(1, sizeof(t_textures));
	if (!game->texture)
		exit((ft_printf("Error\nFailed calloc texture\n"),
				free_texture1(game), EXIT_FAILURE));
	game->texture->floor = mlx_load_png("./images/floor.png");
	game->texture->wall = mlx_load_png("./images/wall.png");
	game->texture->col = mlx_load_png("./images/coconut.png");
	game->texture->player = mlx_load_png("./anim/Wait/wait_1.png");
	game->texture->exit = mlx_load_png("./images/exit.png");
	game->texture->enemy = mlx_load_png("./images/enemy1.png");
	game->texture->win = mlx_load_png("./images/win.png");
	game->texture->loose = mlx_load_png("./images/loose.png");
	if (!game->texture->floor || !game->texture->wall || !game->texture->col
		|| !game->texture->player || !game->texture->exit
		|| !game->texture->enemy || !game->texture->win
		|| !game->texture->loose)
		exit((ft_printf("Error\nFailed to load1 png\n"),
				free_texture1(game), EXIT_FAILURE));
}

void	get_images(t_game *game)
{
	game->img = ft_calloc(1, sizeof(t_images));
	if (!game->img)
		exit((ft_printf("Error\nFailed calloc image\n"),
				free_texture1(game), free_image(game), EXIT_FAILURE));
	game->img->floor = mlx_texture_to_image(game->mlx, game->texture->floor);
	game->img->wall = mlx_texture_to_image(game->mlx, game->texture->wall);
	game->img->col = mlx_texture_to_image(game->mlx, game->texture->col);
	game->img->player = mlx_texture_to_image(game->mlx, game->texture->player);
	game->img->exit = mlx_texture_to_image(game->mlx, game->texture->exit);
	game->img->enemy = mlx_texture_to_image(game->mlx, game->texture->enemy);
	game->img->win = mlx_texture_to_image(game->mlx, game->texture->win);
	game->img->loose = mlx_texture_to_image(game->mlx, game->texture->loose);
	if (!game->img->floor || !game->img->wall || !game->img->col
		|| !game->img->player || !game->img->exit || !game->img->enemy
		|| !game->img->win || !game->img->loose)
		exit((ft_printf("Error\nFailed to load2 image\n"),
				free_texture1(game), free_image(game), EXIT_FAILURE));
	free_texture1(game);
}
