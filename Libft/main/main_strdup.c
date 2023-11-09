/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:48:43 by estosche          #+#    #+#             */
/*   Updated: 2023/10/20 09:44:27 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strdup(const char *src);
int	main(void)
{
	char src[] = "coucou";
	char *dest;

	dest =ft_strdup(src);
	printf("%s\n", dest);
	return 0;
}
