/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strncmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:17:16 by estosche          #+#    #+#             */
/*   Updated: 2023/10/25 10:22:36 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n);

int	main(void)
{
	size_t	n = 5;
	char str1[] = "abcdef";
	char str2[] = "abc\375xx";
	printf("%d\n", ft_strncmp(str1, str2, n));	
	return 0;
}
