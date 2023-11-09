/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:10:16 by estosche          #+#    #+#             */
/*   Updated: 2023/10/17 10:12:45 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *str);

int	main(void)
{
	const char *str;
	size_t	i;

	str = "hello";
	i = ft_strlen(str);
	printf("%ld \n", i);
	return (0);
}
