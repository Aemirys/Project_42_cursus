/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dimension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:06:41 by estosche          #+#    #+#             */
/*   Updated: 2024/10/16 11:00:19 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("file doesn't exist\n");
		return (-4);
	}
	return (fd);
}

bool	ignore_line(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 \
	|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 \
	|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0 \
	|| line[0] == '\0' || line[0] == '\n');
}

void	update_dim(const char *line, size_t *curr_w, size_t *h)
{
	size_t	line_length;

	line_length = ft_strlen(line);
	if (line[line_length - 1] == '\n')
		line_length--;
	if (line_length > *curr_w)
		*curr_w = line_length;
	(*h)++;
}

void	size_map(t_game *game, char **map)
{
	int	i;

	i = 0;
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

void	set_dimens(const char *file, size_t *w, size_t *h, t_gc *gc)
{
	size_t	current_width;
	int		fd;
	char	*line;

	current_width = 0;
	fd = open_file(file);
	if (fd == -4)
		exit ((gc_clean(gc), 1));
	*w = 0;
	*h = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ignore_line(line))
		{
			line = get_next_line((free(line), fd));
			continue ;
		}
		update_dim(line, &current_width, h);
		line = get_next_line((free(line), fd));
	}
	*w = current_width;
	close(fd);
}
