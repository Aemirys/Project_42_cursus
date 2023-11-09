/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_calloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:05:23 by estosche          #+#    #+#             */
/*   Updated: 2023/10/23 15:45:12 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <stdlib.h>
#include "libft.h"

//void	*ft_calloc(size_t count, size_t size);

int	main(void)
{
	void	*tab =ft_calloc(10, sizeof(int));
	int i;

	i = 0;
	if (tab == NULL)
	{
		printf("echec");
		return (1);
	}
	while (i < 10)
	{
		printf("%d\n", *(int *)tab + i);
		i++;
	}
	free(tab);
	return 0;
}
