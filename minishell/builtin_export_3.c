/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:45:23 by lschweit          #+#    #+#             */
/*   Updated: 2024/07/18 15:11:01 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_matching_key(t_key *ikey)
{
	free(ikey->data->env[ikey->index]);
	if (ikey->value)
		return (update_env_with_value(ikey));
	else
		return (update_env_without_value(ikey));
}

int	handle_non_matching_key(t_key *ikey)
{
	size_t	old_size;

	old_size = sizeof(char *) * (ikey->index + 1);
	ikey->data->env = ft_realloc(ikey->data->env, old_size, sizeof(char *) \
	* (ikey->index + 2));
	if (ikey->data->env == NULL)
		return (1);
	if (ikey->value)
	{
		ikey->data->env[ikey->index] = malloc(ft_strlen(ikey->arg_copy) + 1);
		if (!ikey->data->env[ikey->index])
			return (1);
		ft_strcpy(ikey->data->env[ikey->index], ikey->arg_copy);
	}
	else
	{
		ikey->data->env[ikey->index] = malloc(ft_strlen(ikey->key) + 2);
		if (!ikey->data->env[ikey->index])
			return (1);
		ft_strcpy(ikey->data->env[ikey->index], ikey->key);
		ft_strcat(ikey->data->env[ikey->index], "=");
	}
	ikey->data->env[ikey->index + 1] = NULL;
	return (0);
}

int	handle_equal(t_data *data, char *key, char *value, char *arg)
{
	int		j;
	t_key	ikey;

	j = 0;
	while (data->env[j])
	{
		if (is_matching_key(data->env[j], key))
		{
			ikey = (t_key){data, arg, key, value, j};
			return (process_matching_key(&ikey));
		}
		j++;
	}
	ikey = (t_key){data, arg, key, value, j};
	return (handle_non_matching_key(&ikey));
}

int	process_plus_equal(t_data *data, char *arg_copy, char *plus_sign)
{
	char	*key;
	char	*value;

	*plus_sign = '\0';
	value = plus_sign + 2;
	key = arg_copy;
	if (handle_plus_equal(data, arg_copy, key, value) != 0)
		return (1);
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!(str[0] == '_' || (str[0] >= 'a' && str[0] <= 'z') \
	|| (str[0] >= 'A' && str[0] <= 'Z')))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z') \
		|| (str[i] >= 'A' && str[i] <= 'Z') \
		|| (str[i] >= '0' && str[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}
