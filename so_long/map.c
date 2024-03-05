/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:47:15 by estosche          #+#    #+#             */
/*   Updated: 2024/03/04 16:29:19 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit (1);
	}
	return (fd);
}

void	size_map(t_game *game, char **map)
{
	int	i;

	i = 0;
	game->n_col = count_col(game);
	game->map_width = (ft_strlen(map[0]) - 1) * 64;
	while (map[i])
		i++;
	game->map_height = i * 64;
	if (game->map_width > WIDTH)
	{
		game->img_width = WIDTH / (ft_strlen(map[0]) - 1);
		game->map_width = WIDTH;
	}
	else
		game->img_width = 64;
	if (game->map_height > HEIGHT)
		game->img_height = HEIGHT / i;
	else
		game->img_height = 64;
}

void	set_dimensions(const char *filename, size_t *width, size_t *height)
{
	size_t	current_width;
	size_t	line_length;
	int		fd;
	char	*line;

	current_width = 0;
	fd = open_file(filename);
	*width = 0;
	*height = 0;
	line = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_length = ft_strlen(line);
		if (line_length > current_width)
			current_width = line_length;
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	*width = current_width;
	close(fd);
	*width = (*width);
	*height = (*height);
}

char	**read_map(char *script_map, t_game *game)
{
	char	*line;
	size_t	i;
	int		fd;
	char	**tmp;

	set_dimensions(script_map, &game->width, &game->height);
	fd = open(script_map, O_RDONLY);
	if (fd == -1)
		exit((ft_printf("Error opening file"), free(game), EXIT_FAILURE));
	tmp = (char **)malloc((game->height + 1) * sizeof(char *));
	if (tmp == NULL)
		exit((ft_printf("malloc"), free(tmp), EXIT_FAILURE));
	line = get_next_line((i = 0, fd));
	while (line != NULL)
	{
		if (i < game->height)
		{
			tmp[i] = ft_strdup(line);
			if (tmp[i] == NULL)
				exit((ft_printf("strdup\n"), free(tmp), EXIT_FAILURE));
			i++;
		}
		line = get_next_line((free(line), fd));
	}
	return (game->height = i, tmp[i] = NULL, close (fd), tmp);
}
