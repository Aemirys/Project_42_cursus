/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:17:35 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:28:41 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_textures_frame(t_game *game)
{
	int		i;
	char	*idle_paths[4];
	char	*mover_paths[4];
	char	*movel_paths[4];

	i = -1;
	idle_paths[0] = "./anim/Wait/wait_1.png";
	idle_paths[1] = "./anim/Wait/wait_2.png";
	idle_paths[2] = "./anim/Wait/wait_3.png";
	idle_paths[3] = "./anim/Wait/wait_4.png";
	mover_paths[0] = "./anim/Right/stitch_R_1.png";
	mover_paths[1] = "./anim/Right/stitch_R_2.png";
	mover_paths[2] = "./anim/Right/stitch_R_3.png";
	mover_paths[3] = "./anim/Right/stitch_R_4.png";
	movel_paths[0] = "./anim/Left/stitch_L_1.png";
	movel_paths[1] = "./anim/Left/stitch_L_2.png";
	movel_paths[2] = "./anim/Left/stitch_L_3.png";
	movel_paths[3] = "./anim/Left/stitch_L_4.png";
	while (++i < 4)
	{
		game->texture->idle[i] = mlx_load_png(idle_paths[i]);
		game->texture->mr[i] = mlx_load_png(mover_paths[i]);
		game->texture->ml[i] = mlx_load_png(movel_paths[i]);
	}
	verify_load1(game);
}

void	get_textures_frame2(t_game *game)
{
	int		i;
	char	*moved_paths[4];
	char	*moveu_paths[4];

	moveu_paths[0] = "./anim/Up/stitch_U_1.png";
	moveu_paths[1] = "./anim/Up/stitch_U_2.png";
	moveu_paths[2] = "./anim/Up/stitch_U_3.png";
	moveu_paths[3] = "./anim/Up/stitch_U_4.png";
	moved_paths[0] = "./anim/Down/stitch_D_1.png";
	moved_paths[1] = "./anim/Down/stitch_D_2.png";
	moved_paths[2] = "./anim/Down/stitch_D_3.png";
	moved_paths[3] = "./anim/Down/stitch_D_4.png";
	i = -1;
	while (++i < 4)
	{
		game->texture->mu[i] = mlx_load_png(moveu_paths[i]);
		game->texture->md[i] = mlx_load_png(moved_paths[i]);
	}
	verify_load2(game);
}

void	get_images_frame(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		game->img->idle[i] = \
		mlx_texture_to_image(game->mlx, game->texture->idle[i]);
		game->img->mr[i] = \
		mlx_texture_to_image(game->mlx, game->texture->mr[i]);
		game->img->ml[i] = \
		mlx_texture_to_image(game->mlx, game->texture->ml[i]);
		game->img->mu[i] = \
		mlx_texture_to_image(game->mlx, game->texture->mu[i]);
		game->img->md[i] = \
		mlx_texture_to_image(game->mlx, game->texture->md[i]);
	}
	verify_image1(game);
	free_texture2(game);
}
