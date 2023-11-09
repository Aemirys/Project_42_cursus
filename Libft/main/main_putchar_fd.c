/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_putchar_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:17:47 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 10:19:00 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	main(void)
{
	int	file_descriptor = 1;  // Utiliser 1 pour l'affichage standard (stdout)
	char	character = 'A';  // Caractère à écrire
	ft_putchar_fd(character, file_descriptor);
	char	newline = '\n';
	ft_putchar_fd(newline, file_descriptor);
	return 0;
}
