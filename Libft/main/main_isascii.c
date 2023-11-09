/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainisascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:57:27 by estosche          #+#    #+#             */
/*   Updated: 2023/10/17 10:00:49 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isascii(int c);

int	main(void)
{
	int c;
	c = 45;
	if (ft_isascii(c) >= 1)
		printf("%c vrai", c);
	else
		printf("%c faux", c);
	return (0);
}
