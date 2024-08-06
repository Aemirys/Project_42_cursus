/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:38:20 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 12:50:49 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_var(t_data *data, char *arg)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], arg, ft_strlen(arg)) == 0 \
		&& data->env[i][ft_strlen(arg)] == '=')
			break ;
		i++;
	}
	if (data->env[i] == NULL)
		return ;
	free(data->env[i]);
	while (data->env[i + 1])
	{
		data->env[i] = data->env[i + 1];
		i++;
	}
	data->env[i] = NULL;
}

char	**copy_env(t_data *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (data->env[i] != NULL)
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (new_env == NULL)
		return (NULL);
	j = 0;
	while (data->env[j])
	{
		new_env[j] = data->env[j];
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	check_path(t_data *data, char *arg)
{
	if (ft_strncmp(arg, "PATH", 4) == 0 && (arg[4] == '\0' || arg[4] == '='))
	{
		free_path(data);
		data->path = NULL;
	}
}

int	check_unset_options(t_data *data, char **args)
{
	int	k;

	k = 1;
	while (args[k] != NULL)
	{
		if (args[k][0] == '-')
		{
			print_error("minishell: unset: ");
			print_error(args[k]);
			print_error(": invalid option\n");
			print_error("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
			data->exit_code = 2;
			return (1);
		}
		k++;
	}
	return (0);
}

void	builtin_unset(t_data *data, char **args)
{
	int		k;
	char	**new_env;

	if (args[1] == NULL)
		return ;
	if (check_unset_options(data, args))
		return ;
	k = 1;
	while (args[k] != NULL)
	{
		free_env_var(data, args[k]);
		k++;
	}
	new_env = copy_env(data);
	if (new_env == NULL)
		return ;
	free(data->env);
	data->env = new_env;
	k = 1;
	while (args[k] != NULL)
	{
		check_path(data, args[k]);
		k++;
	}
	data->exit_code = 0;
}
