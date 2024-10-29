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
#include "get_next_line_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*extract_line(char **line)
{
	char	*get_line;

	if (*line && **line != '\0')
	{
		get_line = ft_strdup(*line);
		free(*line);
		*line = NULL;
		return (get_line);
	}
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (NULL);
}

char	*read_fd(int fd, char **line)
{
	int		bytes_read;
	char	*temp_line;
	char	*buffer;
	char	*new_temp_line;

	temp_line = *line;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(temp_line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		new_temp_line = ft_strjoin(temp_line, buffer);
		if (!new_temp_line)
			return (free(buffer), free(temp_line), NULL);
		temp_line = new_temp_line;
	}
	free(buffer);
	*line = temp_line;
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*line[1024] = {NULL};
	char		*get_line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line[fd])
		line[fd] = read_fd(fd, &line[fd]);
	if (!line[fd])
		return (NULL);
	get_line = extract_line(&line[fd]);
	return (get_line);
}
