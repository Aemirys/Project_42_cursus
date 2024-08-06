/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:08:49 by estosche          #+#    #+#             */
/*   Updated: 2024/03/18 13:21:11 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_infile(t_pipex *pipex, int *pipe_first_command)
{
	int		infile;

	infile = open(pipex->parent_argv[1], O_RDONLY);
	if (infile == -1)
	{
		close(pipe_first_command[1]);
		error(pipex, 1, pipex->parent_argv[1]);
	}
	return (infile);
}

int	open_outfile(t_pipex *pipex)
{
	int		outfile;
	char	*file_name;

	file_name = pipex->parent_argv[pipex->parent_argc - 1];
	if (pipex->here_doc)
		outfile = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		error(pipex, 1, file_name);
	return (outfile);
}

int	here_doc(t_pipex *pipex, char *delimiter)
{
	int		pipes[2];
	char	*line;

	if (pipe(pipes) == -1)
		error(pipex, 1, NULL);
	while (TRUE)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(0);
		if (!line || (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
				&& line[ft_strlen(delimiter)] == '\n'))
		{
			get_next_line(-1);
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipes[1]);
		free(line);
	}
	close(pipes[1]);
	return (pipes[0]);
}
