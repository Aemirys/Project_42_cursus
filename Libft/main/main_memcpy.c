/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_memcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:20:59 by estosche          #+#    #+#             */
/*   Updated: 2023/10/18 16:06:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);

int	main(void)
{
	char str1[] = "hello, world!";
	char str2[15];

	//ft_memcpy(str2, str1, 15);
	memcpy(str2, str1, 15);
	printf("%s\n", str2);
	return 0;
}
