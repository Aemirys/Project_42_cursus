/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:45:17 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 10:32:09 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	initialize_positions(t_data *data)
{
	data->pos_in = malloc(SIZE_PARSER * sizeof(int));
	if (data->pos_in == NULL)
		return (false);
	ft_memset(data->pos_in, 0, SIZE_PARSER * sizeof(int));
	data->pos_out = malloc(SIZE_PARSER * sizeof(int));
	if (data->pos_out == NULL)
		return (false);
	ft_memset(data->pos_out, 0, SIZE_PARSER * sizeof(int));
	data->pos_h = malloc(SIZE_PARSER * sizeof(int));
	if (data->pos_h == NULL)
		return (false);
	ft_memset(data->pos_h, 0, SIZE_PARSER * sizeof(int));
	return (true);
}

bool	initialize_redir_out(t_data *data)
{
	int	i;

	i = 0;
	data->redir_out = (t_redir **)malloc(sizeof(t_redir *) * SIZE_PARSER);
	if (!data->redir_out)
		return (false);
	while (i < SIZE_PARSER)
	{
		data->redir_out[i] = NULL;
		i++;
	}
	return (true);
}

char	*expand(t_data *data, char *var_name_start)
{
	char	*value;
	char	*var_name_end;
	char	*var_name;
	int		var_name_len;

	var_name_end = var_name_start + 1;
	while (*var_name_end != '\0' && *var_name_end != ' ' \
	&& *var_name_end != '\"' && (ft_isalnum(*var_name_end) \
	|| *var_name_end == '_'))
		var_name_end++;
	var_name_len = var_name_end - var_name_start;
	var_name = malloc(var_name_len + 1);
	if (!var_name)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(var_name, var_name_start + 1, var_name_len - 1);
	var_name[var_name_len - 1] = '\0';
	value = get_env_var(data, var_name);
	free(var_name);
	if (value == NULL)
		return (ft_strdup(""));
	else
		return (value);
}

t_cmd	*create_link_command(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->cmd_tokens = NULL;
	new_cmd->next = NULL;
	new_cmd->content = NULL;
	return (new_cmd);
}

t_cmd	*parser(t_data *data)
{
	t_token	*token;
	t_cmd	*command;
	t_cmd	*current;

	if (!initialize_positions(data) || !initialize_redir_out(data))
		return (NULL);
	token = data->tokens;
	command = create_link_command();
	current = command;
	handle_redir_and_pipes(data, &token, &current);
	current->next = NULL;
	if (data->redir == false)
	{
		free_redir_out_list(data);
	}
	return (command);
}
