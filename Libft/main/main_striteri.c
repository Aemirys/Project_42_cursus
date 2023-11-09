/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_striteri.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:11:40 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 10:13:39 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	print_char_with_index(unsigned int index, char *c)
{
	printf("Character at index %u: %c\n", index, *c);
}

int	main(void) 
{
	char str[] = "Hello, World!";
	ft_striteri(str, print_char_with_index);
	return 0;
}
