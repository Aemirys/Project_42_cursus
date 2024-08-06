/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:40:32 by lschweit          #+#    #+#             */
/*   Updated: 2024/07/17 11:39:39 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path_validity(t_data *data, char *path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
	{
		cd_error(path, "No such file or directory\n", 1);
		data->exit_code = 1;
		return (1);
	}
	if (!S_ISDIR(info.st_mode))
	{
		cd_error(path, "Not a directory\n", 1);
		data->exit_code = 1;
		return (1);
	}
	if (access(path, X_OK) != 0)
	{
		cd_error(path, "Permission denied\n", 1);
		data->exit_code = 1;
		return (1);
	}
	return (0);
}

int	change_directory(t_data *data, char *path)
{
	if (chdir(path) != 0)
	{
		cd_error(path, "No such file or directory\n", 1);
		data->exit_code = 1;
		return (1);
	}
	else
	{
		data->exit_code = 0;
		return (0);
	}
}

int	builtin_cd(t_data *data, char *path)
{
	if (path == NULL)
	{
		path = get_env_var(data, "HOME");
		if (path == NULL)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			data->exit_code = 1;
			return (1);
		}
	}
	if (check_path_validity(data, path) == 0)
	{
		return (change_directory(data, path));
	}
	return (1);
}
