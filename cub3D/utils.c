/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:58:46 by estosche          #+#    #+#             */
/*   Updated: 2024/10/16 11:02:35 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*gc_strdup(t_gc *gc, char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *)gc_malloc(gc, (len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strcpy(dup, s);
	return (dup);
}

void	free_text_ray(t_game *game)
{
	if (game->texture->north)
		mlx_delete_texture(game->texture->north);
	if (game->texture->south)
		mlx_delete_texture(game->texture->south);
	if (game->texture->west)
		mlx_delete_texture(game->texture->west);
	if (game->texture->east)
		mlx_delete_texture(game->texture->east);
	if (game->texture->f)
		mlx_delete_texture(game->texture->f);
	if (game->texture->w)
		mlx_delete_texture(game->texture->w);
	if (game->texture->p)
		mlx_delete_texture(game->texture->p);
	free(game->texture);
}

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

void	clean_gnl_buffer(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}
