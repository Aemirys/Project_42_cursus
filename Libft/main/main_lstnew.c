/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:31:44 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 14:07:31 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)	
{
	t_list	*list;
	int	*data;

	data = malloc(sizeof(int));
	*data = 10;
	list = ft_lstnew(data);
	if (list == NULL)
	{
		printf("erreur de creation de la liste\n");
		return (1);
	}
	printf("la liste contient : %d.\n", *(int *)list->content);
	free(list);
	free(data);
	return 0;
}
