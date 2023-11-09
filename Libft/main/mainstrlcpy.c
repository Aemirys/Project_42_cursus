/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainstrlcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:47:56 by estosche          #+#    #+#             */
/*   Updated: 2023/10/17 15:18:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size);

int	main(void)
{
	char str1[] = "hello,world!";
	char str2[10];
	size_t len = ft_strlcpy(str2, str1, sizeof(str2));
	printf("%s\n", str2);
	printf("%s\n", str1);
	printf("la longueur de la chaine str2 est de %zu caracteres.\n", len);
	if(str2[sizeof (str2) - 1] != '\0')
		{
			printf("test failed!\n");
			return (1);
		}
	else
		printf("test passed!\n");
	return (0);
}
