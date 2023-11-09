/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strlcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:39:51 by estosche          #+#    #+#             */
/*   Updated: 2023/10/24 17:11:59 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <strings.h>

size_t	ft_strlcat(char *dest, const char *src, size_t count);

int	main(void)
{
	char dest[14] = "pqrs";
	char src[] = "abcdefghi";
	//size_t	len;
	
	size_t	len = ft_strlcat(dest, src, 10);
	printf("%s\n", dest);
	printf("%zu\n", len);
	return 0; 
}
