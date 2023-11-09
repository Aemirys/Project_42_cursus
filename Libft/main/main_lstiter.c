/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lstiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:23:16 by estosche          #+#    #+#             */
/*   Updated: 2023/10/31 11:30:11 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
void	print_item(void *item)
{
	printf("%s\n", (char *)item);
}
int	main(void)
{
	t_list *list = ft_lstnew("Hello, wolrd!");
	t_list *list2 = ft_lstnew("Goodbye, world!");

	ft_lstadd_back(&list, list2);

	ft_lstiter(list, print_item);
	return 0;
}
