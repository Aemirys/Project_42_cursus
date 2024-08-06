/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:15:57 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 13:05:19 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->env != NULL)
	{
		while (data->env[i])
		{
			free(data->env[i]);
			data->env[i] = NULL;
			i++;
		}
		free(data->env);
		data->env = NULL;
	}
}

void	free_redir_4(t_redir *redir)
{
	if (redir)
	{
		if (redir->list)
		{
			if (redir->list[0])
				free(redir->list[0]);
			free(redir->list);
		}
		free(redir);
	}
}

void	free_cleaned_value(char **cleaned_value)
{
	int	i;

	i = 0;
	if (cleaned_value)
	{
		while (cleaned_value[i] != NULL)
		{
			free(cleaned_value[i]);
			i++;
		}
		free(cleaned_value);
	}
}

void	free_redir_element(t_redir *current)
{
	int	j;

	j = 0;
	if (current->list)
	{
		while (current->list[j])
		{
			free(current->list[j]);
			j++;
		}
		free(current->list);
	}
	free(current);
}

void	free_redir_out_list(t_data *data)
{
	int		i;
	t_redir	*next;
	t_redir	*current;

	i = 0;
	if (!data || !data->redir_out)
		return ;
	while (i < SIZE_PARSER)
	{
		current = data->redir_out[i];
		while (current)
		{
			next = current->next;
			free_redir_element(current);
			current = next;
		}
		i++;
	}
	free(data->redir_out);
	data->redir_out = NULL;
}
