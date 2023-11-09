/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:01:44 by estosche          #+#    #+#             */
/*   Updated: 2023/10/26 13:17:50 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <string.h>

int	main(void)
{
	char 	*str =  "To be, or not to be, that is the question.";
	char 	**tokens = ft_split(str, ' ');
	for (int i = 0; tokens[i] != NULL; i++)
		printf("%s\n", tokens[i]);

	for (int i = 0; tokens[i] != NULL; i++)
		free (tokens[i]);
	
	free (tokens);
	return (0);
}
