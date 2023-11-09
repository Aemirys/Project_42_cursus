/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strlcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:47:56 by estosche          #+#    #+#             */
/*   Updated: 2023/10/24 16:47:37 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size);

int	main(void)
{
	char dest[15];
	char src[] = "lorem ipsum dolor sit amet";
	size_t len = ft_strlcpy(dest, src, 15);
	printf("%s\n", dest);
	printf("la longueur de la chaine str2 est de %zu caracteres.\n", len);
	if(dest[sizeof (dest) - 1] != '\0')
		{
			printf("test failed!\n");
			return (1);
		}
	else
		printf("test passed!\n");
	return (0);
}
