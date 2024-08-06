/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:56:21 by estosche          #+#    #+#             */
/*   Updated: 2024/04/22 14:17:04 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	init_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	if (argc < 5)
		error(pipex, 3, NULL);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipex->here_doc = TRUE;
	else
		pipex->here_doc = FALSE;
	if (pipex->here_doc && argc < 6)
		error(pipex, 3, NULL);
	pipex->parent_argc = argc;
	pipex->parent_argv = argv;
	pipex->parent_env = env;
	pipex->path = NULL;
	get_path(pipex);
	if (pipex->here_doc)
		return (3);
	return (2);
}

void	get_path(t_pipex *pipex)
{
	char	**path;
	char	**env;

	env = pipex->parent_env;
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (!*env)
		return ;
	*env += 5;
	path = ft_split(*env, ':');
	if (path == NULL)
		error(pipex, 2, NULL);
	pipex->path = path;
}

void	execute(t_pipex *pipex, char *command)
{
	char	*command_file;
	char	*command_not_found;
	char	**command_argv;

	if (command[0] == '\0')
		error(pipex, 127, NULL);
	command_argv = ft_split_quote(command);
	if (command_argv == NULL)
		error(pipex, 2, NULL);
	command_file = find_executable(pipex, command_argv[0]);
	if (command_file == NULL)
	{
		command_not_found = ft_strdup(command_argv[0]);
		ft_free(command_argv);
		error(pipex, 127, command_not_found);
	}
	execve(command_file, command_argv, pipex->parent_env);
}

char	*find_executable(t_pipex *pipex, char *name)
{
	char	*executable;
	char	*tmp;
	int		i;

	if (pipex->path == NULL)
		return (NULL);
	if (access(name, X_OK) == 0)
		return (name);
	i = 0;
	while (pipex->path[i])
	{
		tmp = ft_strjoin(pipex->path[i], "/");
		if (tmp == NULL)
			return (ft_free(pipex->path), NULL);
		executable = ft_strjoin(tmp, name);
		if (executable == NULL)
			return (ft_free(pipex->path), NULL);
		free(tmp);
		if (access(executable, X_OK) == 0)
			return (executable);
		free(executable);
		i++;
	}
	return (NULL);
}

int	get_exit_status(int exit_status)
{
	return (((exit_status & 0xff00)) >> 8);
}
