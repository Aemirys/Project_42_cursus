/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_memmove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:58:53 by estosche          #+#    #+#             */
/*   Updated: 2023/10/24 15:44:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n);

int	main(void)
{
	char src[] = "Hello";
	char dest[] = "Salut1234";
	

	ft_memmove(dest, src, 5);
	//memmove(0, 0, 5);
	printf("%s\n",dest);
	return (0);
}
