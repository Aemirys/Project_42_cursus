/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:15:45 by lschweit          #+#    #+#             */
/*   Updated: 2024/10/16 10:22:38 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	skip_spaces(char **line)
{
	while (**line == ' ')
		(*line)++;
}

bool	parse_component(char **line, int *component)
{
	int	digit_found;

	digit_found = 0;
	*component = 0;
	while (**line >= '0' && **line <= '9')
	{
		*component = *component * 10 + (**line - '0');
		(*line)++;
		digit_found = 1;
	}
	return (digit_found && *component >= 0 && *component <= 255);
}

bool	validate_end(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

int	parse_color(char *line)
{
	int	r;
	int	g;
	int	b;
	int	a;

	a = 255;
	line += 1;
	skip_spaces(&line);
	if (!parse_component(&line, &r) || *line != ',')
		return (-2);
	line++;
	skip_spaces(&line);
	if (!parse_component(&line, &g) || *line != ',')
		return (-2);
	line++;
	skip_spaces(&line);
	if (!parse_component(&line, &b) || !validate_end(line))
		return (-2);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
