/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lstadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:13:18 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 14:29:51 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	t_list	*list = NULL;
	t_list	*link1 = ft_lstnew("Hello, world!");
	t_list	*link2 = ft_lstnew("Goodbye, world!");

	ft_lstadd_front(&list, link1);
	ft_lstadd_front(&list, link2);
	t_list *temp = list;
	if(list != NULL)
		while (list != NULL)
		{
			printf("%s\n", (char *)(list->content));
			list = list->next;
		}
	return 0;
}
