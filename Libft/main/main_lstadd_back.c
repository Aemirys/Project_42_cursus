/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lstadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:17:25 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 16:33:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	t_list	*list = NULL;
	t_list	*link1 = ft_lstnew("Helo, world!");
	t_list	*link2 = ft_lstnew("Goodbye, world!");

	ft_lstadd_back(&list, link1);
	ft_lstadd_back(&list, link2);
	t_list	*temp = list;
	while (temp != NULL)
	{
		printf("%s\n", (char *)(temp->content));
		temp = temp->next;
	}
	return 0;
}
