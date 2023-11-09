/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:26:03 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 09:58:08 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	int	test_numbers[] = {0, 12345, -6789, -2147483648, 42};
	char	*result;
	for (int i = 0; i < sizeof(test_numbers) / sizeof(test_numbers[0]);
			i++) 
	{
		result = ft_itoa(test_numbers[i]);
		if (result)
		{
			printf("ft_itoa(%d) = %s\n", test_numbers[i], result);
			free(result);
		}
		else
		{
			printf("ft_itoa(%d) returned NULL\n", test_numbers[i]);
		}
	}
	return 0;
}
