/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:54:49 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 12:08:00 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data_1(t_data *data)
{
	data->redir = false;
	data->exit_code = 0;
	data->env = NULL;
	data->cwd = NULL;
	data->input_line = NULL;
	data->path = NULL;
	data->quote_open = false;
	data->new_value = NULL;
	data->dollar = false;
	data->d_quotes = false;
	data->s_quote = false;
	data->check_quote = 0;
	data->here_doc = false;
	data->pipes = false;
	data->append = false;
	data->in = false;
	data->redir_in = NULL;
	data->redir_out = NULL;
	data->redir_h = NULL;
	data->pos_in = NULL;
	data->pos_out = NULL;
	data->pos_h = NULL;
	data->redir_out = NULL;
	data->args = NULL;
	return (0);
}

int	init_data_2(t_data *data, char **envp)
{
	int	i;

	data->shit = false;
	data->q_open = false;
	i = 0;
	while (envp[i])
	{
		if (init_env(data, envp, i) == -1)
			return (-1);
		i++;
	}
	get_path(data);
	update_shlvl(data);
	return (0);
}

int	init_data(t_data *data, char **envp)
{
	if (init_data_1(data) == -1)
		return (-1);
	if (init_data_2(data, envp) == -1)
		return (-1);
	return (0);
}
