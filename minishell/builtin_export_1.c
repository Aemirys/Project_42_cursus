/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:43:52 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 13:05:15 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_string(char *str, char **key, char **value)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
	{
		str[i] = '\0';
		*key = str;
		*value = &str[i + 1];
	}
	else
	{
		*key = str;
		*value = "";
	}
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_data *data)
{
	int		j;
	char	*equal_sign;

	sort_env(data->env);
	j = 0;
	while (data->env[j])
	{
		equal_sign = ft_strchr(data->env[j], '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", data->env[j], equal_sign + 1);
			*equal_sign = '=';
		}
		else
			printf("declare -x %s\n", data->env[j]);
		j++;
	}
}

int	update_env(t_env *env)
{
	free(env->data->env[env->j]);
	env->data->env[env->j] = malloc(ft_strlen(env->key) \
	+ 1 + ft_strlen(env->new_value) + 1);
	if (!env->data->env[env->j])
		return (free(env->new_value), free(env->arg_copy), 1);
	ft_strcpy(env->data->env[env->j], env->key);
	ft_strcat(env->data->env[env->j], "=");
	ft_strcat(env->data->env[env->j], env->new_value);
	free(env->new_value);
	free(env->arg_copy);
	return (0);
}

int	handle_env_null(t_env *env, char *value)
{
	size_t	old_size;

	old_size = sizeof(char *) * (env->j + 1);
	env->data->env = ft_realloc(env->data->env, old_size, sizeof(char *) \
	* (env->j + 2));
	if (env->data->env == NULL)
		return (free(env->arg_copy), 1);
	env->data->env[env->j] = malloc(ft_strlen(env->key) \
	+ 1 + ft_strlen(value) + 1);
	if (!env->data->env[env->j])
		return (free(env->arg_copy), 1);
	ft_strcpy(env->data->env[env->j], env->key);
	ft_strcat(env->data->env[env->j], "=");
	ft_strcat(env->data->env[env->j], value);
	env->data->env[env->j + 1] = NULL;
	free(env->arg_copy);
	return (0);
}
