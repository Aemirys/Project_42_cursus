/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:35:00 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 10:52:11 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir_h(t_data *data)
{
	int	i;

	i = 0;
	while (data->redir_h[i])
	{
		free(data->redir_h[i]);
		i++;
	}
	free(data->redir_h);
	data->redir_h = NULL;
}

void	free_redir_in(t_data *data)
{
	int	i;

	i = 0;
	while (data->redir_in[i] != NULL)
	{
		free(data->redir_in[i]);
		i++;
	}
	free(data->redir_in);
	data->redir_in = NULL;
}

void	free_child(t_data *data)
{
	free_redir_2(data);
}

void	free_redir(t_data *data)
{
	if (data->redir_in)
		free(data->redir_in);
	if (data->redir_out)
		free(data->redir_out);
}

void	free_redir_2(t_data *data)
{
	if (data->pos_in != NULL)
	{
		free(data->pos_in);
		data->pos_in = NULL;
	}
	if (data->pos_h != NULL)
	{
		free(data->pos_h);
		data->pos_h = NULL;
	}
	if (data->pos_out != NULL)
	{
		free(data->pos_out);
		data->pos_out = NULL;
	}
}
