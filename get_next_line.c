/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:38:05 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/15 10:38:15 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*extract_and_free_line(char **line)
{
	char	*get_line;
	char	*new_line;
	int		i;

	if (!*line || **line == '\0')
	{
		free(*line);
		*line = NULL;
		return (NULL);
	}
	i = 0;
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if ((*line)[i] == '\n')
	{
		get_line = ft_substr(*line, 0, i + 1);
		new_line = ft_strdup(*line + i + 1);
	}
	else
	{
		get_line = ft_strdup(*line);
		new_line = NULL;
	}
	free(*line);
	return (*line = new_line, get_line);
}

char	*read_fd(int fd, char **line)
{
	int		bytes_read;
	char	*buffer;
	char	*new_temp_line;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(*line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(*line), *line = NULL, NULL);
		buffer[bytes_read] = '\0';
		new_temp_line = ft_strjoin(*line, buffer);
		if (!new_temp_line)
			return (free(buffer), free(*line), *line = NULL, NULL);
		free(*line);
		*line = new_temp_line;
	}
	free(buffer);
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*get_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
		line = ft_strdup("");
	if (!read_fd(fd, &line))
		return (NULL);
	get_line = extract_and_free_line(&line);
	return (get_line);
}
