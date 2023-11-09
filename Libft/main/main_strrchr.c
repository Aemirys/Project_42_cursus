/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:37:27 by estosche          #+#    #+#             */
/*   Updated: 2023/10/25 10:12:08 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *str, int c);

int	main(void)
{
	int c = 'l';
	char str[] = "hello";
	char *ptr;

	ptr = ft_strrchr (str, c);
	if (ptr != NULL)
	{
		printf("la derniere occurrence de '%c' est a l'adresse %ld", c ,(ptr - str));
	}
	return 0;
}
