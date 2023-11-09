/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strmapi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:58:27 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 10:00:25 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	f(unsigned int i, char c)
{
	return (ft_toupper(c));
}
int	main(void)
{
	char	*s = "hello, world!";
	char	*new_s;
	
	new_s = ft_strmapi(s, f);
	if (!new_s)
	{
		printf("Erreur lors de l'allocation de mémoire\n");
		return 1;
	}
	printf("%s\n", new_s);
	free(new_s);
	return 0;
}
