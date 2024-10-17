/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:27:45 by estosche          #+#    #+#             */
/*   Updated: 2024/09/18 11:41:00 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_gc	*gc_init(void)
{
	t_gc	*gc;

	gc = (t_gc *)malloc(sizeof(t_gc));
	if (!gc)
	{
		printf("Error memory allocation\n");
		exit (1);
	}
	gc->block_count = 0;
	return (gc);
}

void	*gc_malloc(t_gc *gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Error memory allocation\n");
		exit(1);
	}
	if (gc->block_count < MAX_BLOCKS)
	{
		gc->blocks[gc->block_count].ptr = ptr;
		gc->blocks[gc->block_count].size = size;
		gc->blocks[gc->block_count].is_use = 1;
		gc->block_count++;
	}
	return (ptr);
}

void	gc_free(t_gc *gc, void *ptr)
{
	size_t	i;

	i = 0;
	while (i < gc->block_count)
	{
		if (gc->blocks[i].ptr == ptr)
		{
			free(gc->blocks[i].ptr);
			gc->blocks[i].ptr = NULL;
			gc->blocks[i].is_use = 0;
			break ;
		}
		i++;
	}
}

void	gc_clean(t_gc *gc)
{
	size_t	i;

	i = 0;
	while (i < gc->block_count)
	{
		if (gc->blocks[i].ptr)
		{
			free(gc->blocks[i].ptr);
			gc->blocks[i].ptr = NULL;
		}
		i++;
	}
	free(gc);
}
