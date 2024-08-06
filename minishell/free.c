/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:28:47 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 10:50:47 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = cmd_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd_tokens)
		{
			i = 0;
			while (current->cmd_tokens[i])
			{
				free(current->cmd_tokens[i]);
				i++;
			}
			free(current->cmd_tokens);
		}
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
	current = NULL;
}

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token != NULL)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		free(temp);
	}
}

void	free_tokens_lexer(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (tokens == NULL || *tokens == NULL)
		return ;
	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	free_pids(t_data *data)
{
	t_pid	*node;
	t_pid	*next_node;

	node = data->pids;
	while (node != NULL)
	{
		next_node = node->next;
		free(node);
		node = next_node;
	}
	data->pids = NULL;
}

void	ft_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
