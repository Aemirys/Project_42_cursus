/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:18:57 by estosche          #+#    #+#             */
/*   Updated: 2024/10/09 10:55:07 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MAX_FILE_OPEN 30

void	free_gnl(char **buffer)
{
	int	i;

	i = 0;
	while (i < MAX_FILE_OPEN)
	{
		if (buffer[i])
			free(buffer[i]);
		i++;
	}
}
