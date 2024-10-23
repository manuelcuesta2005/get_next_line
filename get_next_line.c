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

void	*free_memory(char **buffer, char **lines)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (lines && *lines)
	{
		free(*lines);
		*lines = NULL;
	}
	return (NULL);
}

char	*get_fd(int fd, char **buffer)
{
	char	*temp_bytes;
	char	*new_lines;
	int		read_bytes;

	if (fd < 0)
		return (free_memory(buffer, NULL));
	read_bytes = 1;
	temp_bytes = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_bytes)
		return (free_memory(buffer, NULL));
	while ((!*buffer || !ft_strchr(*buffer, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, temp_bytes, BUFFER_SIZE);
		if (read_bytes < 0)
			return(free_memory(buffer, &temp_bytes));
		temp_bytes[read_bytes] = '\0';
		new_lines = ft_strjoin(*buffer, temp_bytes);
		free(*buffer);
		*buffer = new_lines;
		if (!*buffer)
			return(free_memory(NULL, &temp_bytes));
	}
	free(temp_bytes);
	return (*buffer);
}

char	*reset_fd(char *buffer)
{
	int		start;
	int		i;
	char	*str_reset;

	if (!buffer)
		return (NULL);
	i = 0;
	start = 0;
	while (buffer[start] && buffer[start] != '\n')
		start++;
	if (buffer[start] == '\n')
		start++;
	str_reset = (char *)malloc((ft_strlen(buffer) - start + 1) * sizeof(char));
	if (!str_reset)
		return (NULL);
	while (buffer[start])
		str_reset[i++] = buffer[start++];
	str_reset[i] = '\0';
	free(buffer);
	return (str_reset);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*get_line;

	line = get_fd(fd, &line);
	if (!line)
		return (NULL);
	if (*line == '\0')
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	get_line = set_line(line);
	line = reset_fd(line);
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
	while (lines != NULL)
	{
		printf("%s", lines);
		free(lines);
		lines = get_next_line(fd);
	}
	close(fd);
	return (0);
}