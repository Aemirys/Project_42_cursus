/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:16:48 by estosche          #+#    #+#             */
/*   Updated: 2023/10/25 09:54:33 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c);

int	main(void)
{
	int	c = 'l';
	char	*ptr;
	const	char str[] = "hello, world!";
	ptr = ft_strchr(str, c);
	if (ptr != NULL)
	{
		printf("The character '%c' is found at index %ld\n", c, (ptr - str));
	}
	else
	{
		printf("The character '%c' is not found.\n", c);
	}
	return 0;
	
}

