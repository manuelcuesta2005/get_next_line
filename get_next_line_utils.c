/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:14:52 by mcuesta-          #+#    #+#             */
/*   Updated: 2024/10/14 12:14:54 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;
	size_t	length;

	length = ft_strlen(s) + 1;
	str = (char *)malloc(length * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	if (!s)  // Verificar si 's' es NULL
		return (NULL);
	
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)  // Comparar directamente con 's[i]'
			return ((char *)&s[i]);  // Retornar el puntero al char encontrado
		i++;
	}
	if (c == '\0')  // Comparar 'c' con '\0' sin casteo
		return ((char *)&s[i]);
	
	return (NULL);
}


char	*ft_strjoin(char *let_lines, char *buffer)
{
	char	*new_line;
	int		i;
	int		j;

	if (!let_lines && !buffer)
		return (NULL);
	i = 0;
	j = 0;
	new_line = malloc(((ft_strlen(let_lines) + ft_strlen(buffer)) + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	if (let_lines)
		while (let_lines[i] != '\0')
		{
			new_line[i] = let_lines[i];
			i++;
		}
	while (buffer && buffer[j] != '\0')
	{
		new_line[i] = buffer[j];
		i++;
		j++;
	}
	new_line[i] = '\0';
	if(let_lines)
		free(let_lines);
	return (new_line);
}

