/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_memset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:44:29 by estosche          #+#    #+#             */
/*   Updated: 2023/10/17 10:55:20 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memset(void *ptr, int c, size_t n);

int	main(void)
{
	char str[] = "hello";
	ft_memset(str, '+', 3);
	printf("%s\n", str);
	return (0);
}
