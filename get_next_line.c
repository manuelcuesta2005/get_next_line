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

char	*get_fd(int fd, char *buffer)
{
	char	*temp_bytes;
	int		read_bytes;

	if (fd < 0)
		return (free_memory(NULL, buffer));
	temp_bytes = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_bytes)
		return (free_memory(NULL, buffer));
	while (!buffer || !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, temp_bytes, BUFFER_SIZE);
		if (!read_bytes)
			return(free_memory(temp_bytes, buffer));
		temp_bytes[read_bytes] = '\0';
		buffer = ft_strjoin(buffer, temp_bytes);
		if (!buffer)
			return(free_memory(temp_bytes, buffer));
	}
	free(temp_bytes);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*get_line;

	line = get_fd(fd, line);
	if (!line)
		return (NULL);
	if (*line == '\0')
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	get_line = set_line(line);
	return (get_line);
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