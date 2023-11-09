/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainisalnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:50:45 by estosche          #+#    #+#             */
/*   Updated: 2023/10/17 09:53:19 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isalnum(int c);

int	main(void)
{
	int c;
	c = 'v';
	if (ft_isalnum(c) >= 1)
		printf("%c vrai", c);
	else
		printf("%c faux", c);
}
