/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strtrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:56:57 by estosche          #+#    #+#             */
/*   Updated: 2023/10/25 13:48:18 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	main(void)
{
	char	*str = "   Hello, world!  ";
	char	*result;

	result = ft_strtrim(str, " \t");
	printf("la chaine originale : %s\n", str);
	printf("la chaine sans espace :%s\n", result);
	free (result); // liberer la memoire allouee pour la chaine resultante
	return 0;
}
