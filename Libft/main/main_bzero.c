/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bzero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:29:55 by estosche          #+#    #+#             */
/*   Updated: 2023/10/18 16:33:28 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

//void	ft_bzero(void *ptr, size_t n);

int	main (void)
{
	char str[] = "hello, world!";
	bzero (str, 5);
	printf("%s\n", str);
	return 0;
}
