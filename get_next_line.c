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
#include <stdio.h>

char	*extract_line(char **line)
{
	char	*get_line;

	if (*line && **line != '\0') // Comprobamos que *line contiene texto.
	{
		get_line = ft_strdup(*line);
		free(*line);
		*line = NULL;
		return (get_line);
	}
	if (*line)
	{
		free(*line); // Liberamos solo si contiene texto.
		*line = NULL;
	}
	return (NULL);
}


char	*read_fd(int fd, char **line)
{
	int		bytes_read;
	char	*temp_line = *line;
	char	*buffer;
	char	*new_temp_line;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(temp_line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(temp_line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		new_temp_line = ft_strjoin(temp_line, buffer);
		if (!new_temp_line)
		{
			free(buffer);
			free(temp_line);
			return (NULL);
		}
		temp_line = new_temp_line;
	}
	free(buffer);
	*line = temp_line;
	return (*line);
}


char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*get_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	// Lee el archivo si `line` aún no tiene datos
	if (!line)
		line = read_fd(fd, &line);
	if (!line)
		return (NULL);

	// Extrae y devuelve la siguiente línea o el resto del buffer
	get_line = extract_line(&line);
	return (get_line);
}



// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int fd = open("qj.txt", O_RDONLY);
// 	if (fd < 0)
// 		printf("error al abrir el archivo");
// 	char *lines;
// 	while ((lines = get_next_line(fd)) != NULL)
// 	{	
// 		if(lines == NULL)
// 			printf("patata");
// 		printf("%s", lines);
// 		free(lines);
// 	}
// 	close(fd);
// 	return (0);
// }