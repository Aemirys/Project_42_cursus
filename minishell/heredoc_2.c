/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:09:51 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 13:05:16 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_exit_code;

int	process_heredoc_inner_loop(t_data *data, t_heredoc *info, int i)
{
	char	*line;

	while (g_exit_code != 130)
	{
		line = read_line_and_check_exit(info->fd, info->line_num);
		if (g_exit_code == 130)
			return (close(info->fd), unlink(info->tmpfile), g_exit_code);
		if (!line)
		{
			if (handle_missing_line(data, *(info->line_num), i))
			{
				break ;
			}
		}
		else
		{
			if (check_delimiter_and_write(data, info->fd, line, i))
			{
				free(line);
				break ;
			}
			free(line);
		}
	}
	return (0);
}

int	process_here_doc(t_data *data, char *tmpfile, int fd)
{
	int			i;
	int			line_num;
	t_heredoc	info;

	info.tmpfile = tmpfile;
	info.fd = fd;
	info.line_num = &line_num;
	i = 0;
	line_num = 1;
	while (i < get_array_length(data->redir_h))
	{
		if (process_heredoc_inner_loop(data, &info, i) == 130)
		{
			close(fd);
			return (130);
		}
		i++;
	}
	close(fd);
	return (0);
}

int	open_tmpfile(char *tmpfile)
{
	int	fd;

	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Failed to open temporary file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	here_doc(t_data *data, t_cmd *command)
{
	int		fd;
	char	*tmpfile;

	(void)command;
	tmpfile = "/tmp/heredoc_tmp";
	fd = open_tmpfile(tmpfile);
	handle_signals_heredoc();
	if (process_here_doc(data, tmpfile, fd) == 130)
		return (130);
	return (reopen_tmpfile(tmpfile));
}
