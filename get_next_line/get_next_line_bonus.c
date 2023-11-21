/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:11:32 by estosche          #+#    #+#             */
/*   Updated: 2023/11/21 16:11:40 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#define MAX_FILE_OPEN 30

static char	*ft_free(char *s)
{
	if (s != NULL)
	{
		free(s);
		s = NULL;
	}
	return (NULL);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;
	int		len;

	if (buffer == NULL)
		return (NULL);
	i = 0;
	len = 1;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static	char	*copy_buf(char *buffer, size_t len)
{
	char	*res;
	int		i;
	size_t	buffer_len;
	size_t	len_to_copy;	

	if (!buffer || len <= 0)
		return (NULL);
	i = 0;
	buffer_len = ft_strlen(buffer);
	len_to_copy = buffer_len - len + 1;
	res = (char *)malloc(sizeof(char) * len_to_copy + 1);
	if (!res)
		return (ft_free(buffer));
	while (buffer[len + i] != '\0')
	{
		res[i] = buffer[len + i];
		i++;
	}
	res[i] = '\0';
	free(buffer);
	return (res);
}

char	*read_file(int fd, char *text)
{
	char	*res;
	char	*tmp;
	ssize_t	bytes_read;

	res = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!res || !text)
		return (ft_free(text), ft_free(res), NULL);
	bytes_read = 1;
	while (bytes_read >= 1 && !newline_found(text))
	{
		bytes_read = read(fd, res, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		res[bytes_read] = 0;
		tmp = ft_strjoin(text, res);
		ft_free(text);
		if (tmp == NULL)
			return (ft_free(res));
		text = tmp;
	}
	free(res);
	if (bytes_read < 0 || !text || !text[0])
		return (ft_free(text));
	return (text);
}

char	*get_next_line(int fd)
{
	static char	*buffers[MAX_FILE_OPEN] = {NULL};
	char		*line;

	if (fd < 0 || fd >= MAX_FILE_OPEN || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffers[fd])
	{
		buffers[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffers[fd])
			return (NULL);
		*buffers[fd] = '\0';
	}
	buffers[fd] = read_file(fd, buffers[fd]);
	if (!buffers[fd] || buffers[fd][0] == '\0')
		return (NULL);
	line = extract_line(buffers[fd]);
	if (!line || line[0] == '\0')
	{
		if (line)
			ft_free(buffers[fd]);
		return (ft_free(line));
	}
	buffers[fd] = copy_buf(buffers[fd], ft_strlen(line));
	return (line);
}
