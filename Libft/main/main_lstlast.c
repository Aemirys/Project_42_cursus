/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lstlast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:56:19 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 15:09:18 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	t_list	*list = NULL;
	t_list	*link1= ft_lstnew("Hello, world!");
	t_list	*link2 = ft_lstnew("Goodbye, world!");

	ft_lstadd_front(&list, link1);
	ft_lstadd_front(&list, link2);
	
	t_list	*temp = list;
	while(temp != NULL)
	{
		printf("%s\n", (char *)(temp->content));
		temp = temp ->next;
	}
	t_list	*last = ft_lstlast(list);
	if(last != NULL)
		printf("Dernier element : %s\n", (char *)(last->content));
	else
		printf("la liste est vide.\n");
	return 0;
}
