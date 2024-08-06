/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:26:39 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 13:05:15 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_data *data, char **envp, int i)
{
	char	**new_env;
	int		j;

	j = 0;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (new_env == NULL)
		return (perror("Error allocating memory"), -1);
	while (j < i)
	{
		new_env[j] = data->env[j];
		j++;
	}
	if (data->env != NULL)
		free(data->env);
	new_env[i] = ft_strdup(envp[i]);
	if (new_env[i] == NULL)
	{
		perror("Error duplicating environment variable");
		free(new_env);
		return (-1);
	}
	new_env[i + 1] = NULL;
	data->env = new_env;
	return (0);
}

void	update_shlvl(t_data *data)
{
	int		i;
	char	*shlvl;
	int		level;

	i = 0;
	while (data->env[i] && ft_strncmp(data->env[i], "SHLVL", 5) != 0)
		i++;
	if (data->env[i])
	{
		level = ft_atoi(data->env[i] + 6);
		level++;
		shlvl = ft_itoa(level);
		free(data->env[i]);
		data->env[i] = ft_strjoin("SHLVL=", shlvl);
		free(shlvl);
	}
}

void	decrement_shlvl(t_data *data)
{
	int		i;
	char	*shlvl;
	int		level;

	i = 0;
	while (data->env[i] && ft_strncmp(data->env[i], "SHLVL", 5) != 0)
		i++;
	if (data->env[i])
	{
		level = ft_atoi(data->env[i] + 6);
		level--;
		shlvl = ft_itoa(level);
		free(data->env[i]);
		data->env[i] = ft_strjoin("SHLVL=", shlvl);
		free(shlvl);
	}
}

char	*get_env_var(t_data *data, char *var_name)
{
	int		i;
	char	*env_entry;
	char	*value_start;

	if (data->env == NULL)
		return (NULL);
	i = 0;
	while (data->env[i])
	{
		env_entry = data->env[i];
		if (ft_strncmp(env_entry, var_name, ft_strlen(var_name)) == 0 \
		&& env_entry[ft_strlen(var_name)] == '=')
		{
			value_start = &env_entry[ft_strlen(var_name) + 1];
			return (value_start);
		}
		i++;
	}
	return (NULL);
}
