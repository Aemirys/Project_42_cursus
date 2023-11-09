/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainisprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:03:50 by estosche          #+#    #+#             */
/*   Updated: 2023/10/17 10:06:04 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isprint(int c);

int	main(void)
{
	int c;
	c = 25;
	if (ft_isprint(c) >= 1)
		printf("%c vrai", c);
	else
		printf("%c faux", c);
}
