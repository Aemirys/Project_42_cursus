/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:53:49 by estosche          #+#    #+#             */
/*   Updated: 2024/03/18 09:46:07 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_command(t_pipex *pipex)
{
	int		infile;
	int		pipes[2];
	pid_t	pid;

	if (pipe(pipes) == -1)
		error(pipex, 1, NULL);
	if (pipex->here_doc == TRUE)
		infile = here_doc(pipex, pipex->parent_argv[2]);
	pid = fork();
	if (pid == 0)
	{
		close(pipes[0]);
		if (pipex->here_doc == FALSE)
			infile = open_infile(pipex, pipes);
		dup2(infile, STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
		close(infile);
		close(pipes[1]);
		execute(pipex, pipex->parent_argv[2 + pipex->here_doc]);
	}
	dup2(pipes[0], STDIN_FILENO);
	close_pipe (pipes);
	if (pipex->here_doc == TRUE)
		close(infile);
}

void	middle_commands(t_pipex *pipex, int command_index)
{
	char	*middle_command;
	int		pipes[2];
	pid_t	pid;

	middle_command = pipex->parent_argv[command_index];
	if (pipe(pipes) == -1)
		error(pipex, 1, NULL);
	pid = fork();
	if (pid == 0)
	{
		close(pipes[0]);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[1]);
		execute(pipex, middle_command);
	}
	else
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
	}
}

void	last_command(t_pipex *pipex)
{
	char	*last_command;
	int		exit_status;
	int		outfile;
	pid_t	pid;

	last_command = pipex->parent_argv[pipex->parent_argc - 2];
	pid = fork();
	if (pid == 0)
	{
		outfile = open_outfile(pipex);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		execute(pipex, last_command);
	}
	waitpid(pid, &exit_status, 0);
	pipex->exit_status_last_command = exit_status;
}

void	create_childs(t_pipex *pipex, int command_index)
{
	if (command_index == 2 || (command_index == 3 && pipex->here_doc))
		first_command(pipex);
	else if (command_index == pipex->parent_argc - 2)
		last_command(pipex);
	else
		middle_commands(pipex, command_index);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex		pipex;
	int			command_index;

	command_index = init_pipex(&pipex, argc, argv, env);
	while (command_index <= argc - 2)
		create_childs(&pipex, command_index++);
	if (pipex.path)
		ft_free(pipex.path);
	exit(get_exit_status(pipex.exit_status_last_command));
}
