/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:21:13 by estosche          #+#    #+#             */
/*   Updated: 2023/10/24 16:27:33 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *str);
int	main(void)
{
	char str[] = "\n\n\n  -46\b9 \n5d6";
	int n =ft_atoi(str);
	printf("la valeur de l'entier est %d\n", n);
	return 0;
}
