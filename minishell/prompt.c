/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:49:44 by estosche          #+#    #+#             */
/*   Updated: 2024/07/01 14:12:57 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_data *data)
{
	char		*cwd;
	char		*temp;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	data->prompt = ft_strjoin(ANSI_COLOR_CYAN, cwd);
	temp = data->prompt;
	data->prompt = ft_strjoin(temp, " $> " ANSI_COLOR_RESET);
	free(temp);
	free(cwd);
}
