/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:37:22 by estosche          #+#    #+#             */
/*   Updated: 2024/03/13 16:57:04 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(t_pipex *pipex, char *command)
{
	char	*executable;

	pipex->argv_childs = ft_split_quote(command);
	if (pipex->argv_childs == NULL)
		error(pipex, 2, NULL);
	executable = find_executable(pipex);
	if (executable == NULL)
		error(pipex, 127, NULL);
	execve(executable, pipex->argv_childs, pipex->parent_env);
}

char	*find_executable(t_pipex *pipex)
{
	char	*executable;
	char	*command;
	char	*tmp;
	int		i;

	command = pipex->argv_childs[0];
	if (access(command, X_OK) == 0)
		return (command);
	i = 0;
	while (pipex->path[i])
	{
		tmp = ft_strjoin(pipex->path[i], "/");
		executable = ft_strjoin(tmp, command);
		free(tmp);
		if (access(executable, X_OK) == 0)
			return (executable);
		free(executable);
		i++;
	}
	return (NULL);
}

void	first_child(t_pipex *pipex, char *command)
{
	int	infile;

	pipex->first_child = fork();
	if (pipex->first_child == 0)
	{
		close(pipex->pipe[0]);
		infile = open(pipex->parent_argv[1], O_RDONLY);
		if (infile == -1)
		{
			close(pipex->pipe[1]);
			ft_free(pipex->path);
			error(pipex, 1, pipex->parent_argv[1]);
		}
		dup2(pipex->pipe[1], STDOUT_FILENO);
		dup2(infile, STDIN_FILENO);
		close(pipex->pipe[1]);
		close(infile);
		execute(pipex, command);
	}
}

void	second_child(t_pipex *pipex, char *command)
{
	int	outfile;

	pipex->second_child = fork();
	if (pipex->second_child == 0)
	{
		close(pipex->pipe[1]);
		outfile = open(pipex->parent_argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (outfile == -1)
		{
			close(pipex->pipe[0]);
			ft_free(pipex->path);
			error(pipex, 1, pipex->parent_argv[4]);
		}
		dup2(pipex->pipe[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(pipex->pipe[0]);
		close(outfile);
		execute(pipex, command);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		exit_status;

	init_pipex(&pipex, argc, argv, env);
	first_child(&pipex, argv[2]);
	second_child(&pipex, argv[3]);
	close_pipe(&pipex);
	waitpid(pipex.second_child, &exit_status, 0);
	ft_free(pipex.path);
	exit(get_exit_status(exit_status));
}
