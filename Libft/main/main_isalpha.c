/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_isalpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:34:36 by estosche          #+#    #+#             */
/*   Updated: 2023/10/23 11:54:01 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

//int	ft_isalpha (int c);

int	main(void)
{
	int	c;

	c = 'a';
	if(ft_isalpha(c) >= 1)
		printf("%c est un caractere", c);
	else
		printf("%c n'est pas un caractere", c);
	return (0);	
}
