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
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	int			i;
	char		*str;
	size_t		length;

	length = ft_strlen(s) + 1;
	str = (char *) malloc(length * sizeof(char));
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
	char	*foundchar;

	i = 0;
	foundchar = (char *)s;
	while (s[i] != '\0')
	{
		if (foundchar[i] == (unsigned char)c)
			return (&foundchar[i]);
		i++;
	}
	if (s[i] == '\0' && (unsigned char)c == '\0')
		return (&foundchar[i]);
	return (NULL);
}

char	*ft_strjoin(char *let_lines, char *buffer)
{
	char	*new_line;
	int		len_join;
	int		i;
	int		j;

	if (!let_lines && !buffer)
		return (NULL);
	if (!let_lines)
		return (ft_strdup(buffer));
	if (!buffer)
		return (ft_strdup(let_lines));
	i = 0;
	j = 0;
	len_join = ft_strlen(let_lines) + ft_strlen(buffer);
	new_line = (char *) malloc((len_join + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	while (let_lines[i++] != '\0')
		new_line[i] = let_lines[i];
	while (buffer[j] != '\0')
		new_line[i++] = buffer[j++];
	new_line[i] = '\0';
	free(let_lines);
	return (new_line);
}
