/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:47:17 by lschweit          #+#    #+#             */
/*   Updated: 2024/07/18 15:55:48 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_history(void)
{
	HIST_ENTRY	**histo_list;
	int			i;

	histo_list = history_list();
	if (histo_list)
	{
		i = 0;
		while (histo_list[i])
		{
			printf("%d %s\n", i + 1, histo_list[i]->line);
			i++;
		}
	}
}

void	handle_history(void)
{
	print_history();
}
