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
#include <stdlib.h>
#include <unistd.h>

char	*free_memory(char *buffer, char *lines)
{
	free(buffer);
	free(lines);
	return (NULL);
}

char	*read_fd(int fd, char *lines)
{
	int		bytes;
	char	*temporal_buffer;

	bytes = 1;
	temporal_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temporal_buffer)
		return (free_memory(NULL, lines));
	while ((!lines || !ft_strchr(lines, '\n')))
	{
		bytes = read(fd, temporal_buffer, BUFFER_SIZE);
		if (bytes == -1)
			return(free_memory(temporal_buffer, lines));
		if (ft_strchr(temporal_buffer, '\n'))
		{
			temporal_buffer[bytes] = '\0';
			lines = ft_strjoin(lines, temporal_buffer);
			lines = ft_strjoin(lines, "\n");
		}
		if (!lines)
			return (free_memory(temporal_buffer, NULL));
	}
	free(temporal_buffer);
	return (lines);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;

	line = read_fd(fd, line);
	if (!line)
		return (NULL);
	if (*line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("archivo.txt", O_RDONLY);
	if (fd < 0)
		printf("error al abrir el archivo");
	char *lines = get_next_line(fd);
	printf("%s", lines);
	close(fd);
	return (0);
}