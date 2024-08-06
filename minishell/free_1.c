/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:53:29 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 13:05:15 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_builtins(t_data *data)
{
	free_child(data);
	free_redir_2(data);
	free_tokens(data->tokens);
	free_env(data);
	free_path(data);
	free_prompt(data);
	free_cmd_list(data->commands);
	free_pids(data);
	if (data->redir_h != NULL)
		free_redir_h(data);
	if (data->redir_out != NULL)
	{
		if (data->redir_out[data->command_index] != NULL)
			free_redir_out_list(data);
	}
	if (data->redir_in != NULL)
		free_redir_in(data);
}

void	free_path(t_data *data)
{
	int	i;

	i = 0;
	if (data->path != NULL)
	{
		while (data->path[i] != NULL)
		{
			free(data->path[i]);
			i++;
		}
		free(data->path);
		data->path = NULL;
	}
}

void	free_prompt(t_data *data)
{
	if (data->prompt != NULL)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
}

void	free_all(t_data *data)
{
	if (data->path != NULL)
		free_path(data);
	if (data->prompt != NULL)
		free_prompt(data);
}
