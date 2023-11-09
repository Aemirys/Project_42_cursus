/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_memcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:19:54 by estosche          #+#    #+#             */
/*   Updated: 2023/10/25 10:35:05 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *str1, const void *str2, size_t n);

int main(void)
{
	
	char str1[] = "\xff\0\0\xaa\0\xde\xffMACOSX\xff";
	char str2[] = "\xff\0\0\xaa\0\xde\x00MBS";
	printf("%d\n", ft_memcmp(str1, str2, 9));
	return 0;
}
