/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:39:39 by estosche          #+#    #+#             */
/*   Updated: 2024/10/16 13:17:47 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_ignored_line(char *line)
{
	return (ft_strncmp(line, "\n", 1) == 0);
}

char	**read_map_data(int fd, t_game *game, t_gc *gc, char *line)
{
	char	**tmp;
	size_t	i;

	i = 0;
	tmp = (char **)gc_malloc(gc, (game->height + 1) * sizeof(char *));
	if (tmp == NULL)
		exit((printf("malloc\n"), gc_clean(gc), free(game), EXIT_FAILURE));
	tmp[i] = gc_strdup(gc, line);
	if (tmp[i] == NULL)
		exit((printf("strdup\n"), gc_clean(gc), free(tmp), EXIT_FAILURE));
	free(line);
	i++;
	line = get_next_line(fd);
	while (line != NULL && i < game->height)
	{
		tmp[i] = gc_strdup(gc, line);
		if (tmp[i] == NULL)
			exit((printf("strdup\n"), gc_clean(gc), free(tmp), EXIT_FAILURE));
		free(line);
		i++;
		line = get_next_line(fd);
	}
	tmp[i] = NULL;
	game->height = i;
	return (tmp);
}

int	handle_colors(char *line, t_game *game)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		game->floor_color = parse_color(line);
		if (game->floor_color == -2)
			return (printf("Error\nInvalid floor color format\n"), -5);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		game->ceiling_color = parse_color(line);
		if (game->ceiling_color == -2)
			return (printf("Error\nInvalid ceiling color format\n"), -5);
	}
	return (0);
}

char	*extract_path(char *line)
{
	char	*path;

	if (ft_strncmp(line, "NO ", 3) == 0)
		path = line + 3;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		path = line + 3;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		path = line + 3;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		path = line + 3;
	else
		return (NULL);
	while (*path == ' ' || *path == '\t')
		path++;
	return (path);
}

int	load_texture_path(char *line, t_game *game, t_gc *gc)
{
	char	*path;
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	path = extract_path(line);
	if (!path)
	{
		if (handle_colors(line, game) == -5)
			return (-5);
		return (0);
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->texture_paths[0] = gc_strdup(gc, path);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->texture_paths[1] = gc_strdup(gc, path);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->texture_paths[2] = gc_strdup(gc, path);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->texture_paths[3] = gc_strdup(gc, path);
	return (0);
}
