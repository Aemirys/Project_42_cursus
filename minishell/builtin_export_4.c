/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:43:49 by lschweit          #+#    #+#             */
/*   Updated: 2024/07/18 15:11:21 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_invalid_identifier(t_data *data, char *key, char *arg_copy)
{
	print_error("minishell: export: `");
	print_error(key);
	print_error("': not a valid identifier\n");
	data->exit_code = 1;
	free(arg_copy);
	return (1);
}

int	validate_arg_copy(t_data *data, char *arg_copy)
{
	if (arg_copy == NULL)
		return (1);
	if (ft_strstr(arg_copy, "-=") != NULL)
		return (handle_error(data, arg_copy));
	return (0);
}

int	process_arg(t_data *data, char *arg)
{
	char	*arg_copy;
	char	*plus_sign;
	char	*key;
	char	*value;

	arg_copy = ft_strdup(arg);
	if (validate_arg_copy(data, arg_copy) != 0)
		return (1);
	plus_sign = ft_strchr(arg_copy, '+');
	if (plus_sign != NULL && *(plus_sign + 1) == '=')
	{
		if (process_plus_equal(data, arg_copy, plus_sign) != 0)
			return (1);
	}
	else
	{
		split_string(arg_copy, &key, &value);
		if (!is_valid_identifier(key))
			return (handle_invalid_identifier(data, key, arg_copy));
		if (handle_equal(data, key, value, arg) != 0)
			return (1);
		free(arg_copy);
	}
	return (0);
}

int	check_export_options(t_data *data, char **args)
{
	int	k;

	k = 1;
	while (args[k] != NULL)
	{
		if (args[k][0] == '-')
		{
			print_error("minishell: export: ");
			print_error(args[k]);
			print_error(": invalid option\n");
			print_error("export: usage: export [-fn] ");
			print_error("[name[=value] ...] or export -p\n");
			data->exit_code = 2;
			return (1);
		}
		k++;
	}
	return (0);
}

int	builtin_export(t_data *data, char **args)
{
	int	i;

	if (args[1] == NULL)
		return (print_export(data), 0);
	if (check_export_options(data, args))
		return (1);
	i = 1;
	while (args[i] != NULL)
	{
		if (process_arg(data, args[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
