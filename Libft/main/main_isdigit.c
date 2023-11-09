/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_isdigit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:40:43 by estosche          #+#    #+#             */
/*   Updated: 2023/10/23 15:12:54 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_isdigit(int c);

int	main(void)
{
	int	c;
	c = '1';
	if (ft_isdigit(c) >= 1)
		printf("%c est un decimal", c);
	else
		printf("%c n'est pas un decimal", c);
}
