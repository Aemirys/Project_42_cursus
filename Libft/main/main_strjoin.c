/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:43:27 by estosche          #+#    #+#             */
/*   Updated: 2023/10/24 10:27:55 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	main(void)
{
	char *s1 = "Hello";
	char *s2 = "world!";

	char *result = ft_strjoin(s1, s2);
	printf("%s\n", result);
	return 0;
}
