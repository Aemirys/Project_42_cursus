/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lstsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:36:15 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 14:52:17 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	t_list	*list = NULL;
	t_list	*link1 = ft_lstnew("Hello, worl!");
	t_list	*link2 = ft_lstnew("Goodbye, world!");

	ft_lstadd_front(&list, link1);
	ft_lstadd_front(&list, link2);

	t_list	*temp = list;
	while(temp != NULL)
	{
		printf("%s\n", (char *)(temp->content));
		temp = temp->next;
	}
	int	size = ft_lstsize(list);
	printf("Taille de la liste : %d\n", size);
	return 0;
}
