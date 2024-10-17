/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:17:19 by estosche          #+#    #+#             */
/*   Updated: 2024/10/17 13:04:35 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_color(char *line, t_game *game, t_gc *gc)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (game->has_floor)
		{
			printf("Error\nDuplicate floor definition (F)\n");
			return (-1);
		}
		game->has_floor = 1;
		if (load_texture_path(line, game, gc) == -5)
			return (-1);
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (game->has_c)
		{
			printf("Error\nDuplicate ceiling definition (C)\n");
			return (-1);
		}
		game->has_c = 1;
		if (load_texture_path(line, game, gc) == -5)
			return (-1);
		return (1);
	}
	return (0);
}

int	handle_texture_or_color(char *line, int fd, t_game *game, t_gc *gc)
{
	int	result;

	result = handle_texture(line, game, gc);
	if (result == 1)
		return (1);
	else if (result == -1)
	{
		free(line);
		clean_gnl_buffer(fd);
		close(fd);
		gc_clean(gc);
		exit(EXIT_FAILURE);
	}
	result = handle_color(line, game, gc);
	if (result == 1)
		return (1);
	else if (result == -1)
	{
		free(line);
		clean_gnl_buffer(fd);
		close(fd);
		gc_clean(gc);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	check_floor_and_ceiling(char *line, t_game *game, t_gc *gc)
{
	if (!game->has_floor || !game->has_c)
	{
		printf("Error\nMissing floor (F) or ceiling (C) definition\n");
		free(line);
		clean_gnl_buffer(game->fd);
		close(game->fd);
		gc_clean(gc);
		exit(EXIT_FAILURE);
	}
}

char	**read_map(char *script_map, t_game *g, t_gc *gc)
{
	char	*line;
	char	**map;

	g->fd = open(script_map, O_RDONLY);
	if (g->fd == -1)
		exit((printf("Error open\n"), gc_clean(gc), free(g), EXIT_FAILURE));
	line = get_next_line(g->fd);
	while (line != NULL)
	{
		if (handle_texture_or_color(line, g->fd, g, gc))
		{
			line = get_next_line((free(line), g->fd));
			continue ;
		}
		else if (is_ignored_line(line))
		{
			line = get_next_line((free(line), g->fd));
			continue ;
		}
		else
			break ;
		line = get_next_line((free(line), g->fd));
	}
	check_floor_and_ceiling(line, g, gc);
	return (map = read_map_data(g->fd, g, gc, line), close(g->fd), map);
}
