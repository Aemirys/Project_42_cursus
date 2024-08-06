/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:44:14 by lschweit          #+#    #+#             */
/*   Updated: 2024/07/04 15:29:11 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_matching_key(char *env_entry, char *key)
{
	return (ft_strncmp(env_entry, key, ft_strlen(key)) == 0 \
		&& (env_entry[ft_strlen(key)] == '=' \
		|| env_entry[ft_strlen(key)] == '\0'));
}

int	process_existing_key(t_key *ikey)
{
	char	*old_val;
	char	*new_val;
	t_env	env;

	old_val = ft_strchr(ikey->data->env[ikey->index], '=');
	if (old_val)
		old_val++;
	else
		old_val = "";
	new_val = malloc(ft_strlen(old_val) + ft_strlen(ikey->value) + 1);
	if (!new_val)
		return (free(ikey->arg_copy), 1);
	ft_strcpy(new_val, old_val);
	ft_strcat(new_val, ikey->value);
	env = (t_env){ikey->data, ikey->arg_copy, ikey->key, new_val, ikey->index};
	return (update_env(&env));
}

int	handle_plus_equal(t_data *data, char *arg_copy, char *key, char *value)
{
	int		j;
	t_env	env;
	t_key	ikey;

	j = 0;
	while (data->env[j])
	{
		if (is_matching_key(data->env[j], key))
		{
			ikey = (t_key){data, arg_copy, key, value, j};
			return (process_existing_key(&ikey));
		}
		j++;
	}
	if (data->env[j] == NULL)
	{
		env = (t_env){data, arg_copy, key, NULL, j};
		return (handle_env_null(&env, value));
	}
	return (0);
}

int	update_env_with_value(t_key *ikey)
{
	ikey->data->env[ikey->index] = malloc(ft_strlen(ikey->arg_copy) + 1);
	if (!ikey->data->env[ikey->index])
		return (1);
	ft_strcpy(ikey->data->env[ikey->index], ikey->arg_copy);
	return (0);
}

int	update_env_without_value(t_key *ikey)
{
	ikey->data->env[ikey->index] = malloc(ft_strlen(ikey->key) + 2);
	if (!ikey->data->env[ikey->index])
		return (1);
	ft_strcpy(ikey->data->env[ikey->index], ikey->key);
	ft_strcat(ikey->data->env[ikey->index], "=");
	return (0);
}
