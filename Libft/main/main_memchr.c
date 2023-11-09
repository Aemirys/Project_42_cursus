/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_memchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:43:34 by estosche          #+#    #+#             */
/*   Updated: 2023/10/19 11:15:39 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n);

int	main(void)
{
	int c = 'H';
	char str[] = "Hello, world!";
	void *ptr;
	ptr = memchr(str, c, strlen(str));
	if (ptr != NULL)
		printf("le caractere '%c' a ete trouve a l'adresse %p\n",c, ptr);
	else
		printf("le caractere '%c' n'a pas ete trouve\n", c);
	return 0;
}
