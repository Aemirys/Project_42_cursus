/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:36:21 by estosche          #+#    #+#             */
/*   Updated: 2024/02/27 13:55:30 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_game *game)
{
	size_t	i;

	i = 0;
	if (game == NULL || game->map == NULL)
	{
		printf("Error: game or game->map is NULL\n");
		return ;
	}
	while (i < game->height)
	{
		if (game->map[i] != NULL)
			ft_printf("%s", game->map[i]);
		else
			printf("Error: game->map[%zu] is NULL\n", i);
		i++;
	}
}
