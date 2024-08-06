/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:40:52 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 11:52:26 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

void	*ft_realloc_parser(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = (malloc(new_size));
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

void	*ft_realloc_2args(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

int	count_commands(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*current_cmd;

	count = 0;
	current_cmd = cmd_list;
	while (current_cmd != NULL)
	{
		count++;
		current_cmd = current_cmd->next;
	}
	return (count);
}

void	count_pid(t_data *data)
{
	int		i;
	t_pid	*node;

	i = 0;
	data->pids = NULL;
	while (i < data->num_cmds)
	{
		node = (t_pid *)malloc(sizeof(t_pid));
		if (node == NULL)
			exit ((perror("malloc pid:"), EXIT_FAILURE));
		node->pid = i;
		node->next = data->pids;
		data->pids = node;
		i++;
	}
}
