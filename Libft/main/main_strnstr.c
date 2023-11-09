/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strnstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:26:43 by estosche          #+#    #+#             */
/*   Updated: 2023/10/24 13:48:53 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
#include "libft.h"
//char	*ft_strnstr(const char *big, const char *little, size_t len);

int	main(void)
{
	char big[] = "Hello, world en anglais!";
	char little[] = "ld";
	char *ptr = ft_strnstr(big, little, strlen(big));

	if (ptr != NULL)
		printf("la sous-chaine trouvee est : %s\n", ptr);
	else
		printf("la sous-chaine n'a pas ete trouvee\n");
	return (0);
}
