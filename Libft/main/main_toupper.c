/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_toupper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:36:43 by estosche          #+#    #+#             */
/*   Updated: 2023/10/18 17:02:12 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
int	ft_toupper(int c);

int	main(void)
{
	int	c;
	
	c = ft_toupper('a');
	printf("%c\n", c);
	return 0;
}
