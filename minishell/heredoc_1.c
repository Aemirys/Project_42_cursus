/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:12:01 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 12:56:44 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_exit_code;

int	reopen_tmpfile(char *tmpfile)
{
	int	fd;

	fd = open(tmpfile, O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open temporary file");
		exit(EXIT_FAILURE);
	}
	unlink(tmpfile);
	return (fd);
}

int	handle_missing_line(t_data *data, int line_num, int i)
{
	ft_putstr_fd("\nminishell: warning:", STDERR_FILENO);
	ft_putstr_fd(" here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(line_num, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file", STDERR_FILENO);
	ft_putstr_fd(" (wanted `", STDERR_FILENO);
	ft_putstr_fd(data->redir_h[i], STDERR_FILENO);
	ft_putstr_fd("`)\n", STDERR_FILENO);
	return (1);
}

int	check_delimiter_and_write(t_data *data, int fd, char *line, int i)
{
	if (ft_strncmp(line, data->redir_h[i], ft_strlen(data->redir_h[i])) == 0 \
	&& line[ft_strlen(data->redir_h[i])] == '\n')
		return (1);
	if (i == get_array_length(data->redir_h) - 1)
		ft_putstr_fd(line, fd);
	return (0);
}

char	*read_line_heredoc(int fd)
{
	t_h_read	h;

	h.line = NULL;
	h.temp = NULL;
	h.total_length = 0;
	while (1)
	{
		h.bytes_read = read(fd, h.buffer, BUFFER_SIZE - 1);
		if (h.bytes_read == -1)
			return (free(h.line), NULL);
		if (h.bytes_read == 0)
			break ;
		h.buffer[h.bytes_read] = '\0';
		h.temp = ft_realloc_2args(h.line, h.total_length + h.bytes_read + 1);
		if (!h.temp)
			return (free(h.line), perror("Failed memory"), NULL);
		h.line = h.temp;
		ft_strcpy(h.line + h.total_length, h.buffer);
		h.total_length += h.bytes_read;
		if (ft_strchr(h.buffer, '\n'))
			break ;
	}
	if (h.bytes_read == -1)
		return (free(h.line), NULL);
	return (h.line);
}

char	*read_line_and_check_exit(int fd, int *line_num)
{
	char	*line;

	(void)fd;
	ft_putstr_fd("> ", STDOUT_FILENO);
	line = read_line_heredoc(STDIN_FILENO);
	if (line)
		(*line_num)++;
	return (line);
}
