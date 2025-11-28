/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:36:49 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/18 22:05:07 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	reflect_lines(int bytes, char **buffer, char **lines, int fd)
{
	char	*new_lines;

	while (bytes > 0)
	{
		(*buffer)[bytes] = '\0';
		new_lines = ft_strjoin(*lines, *buffer);
		free(*lines);
		*lines = new_lines;
		if (!(*lines))
		{
			free(*buffer);
			return (0);
		}
		if (ft_strchr(*buffer, '\n'))
			break ;
		bytes = read(fd, *buffer, BUFFER_SIZE);
	}
	free(*buffer);
	if (bytes < 0)
	{
		free(*lines);
		return (0);
	}
	return (1);
}

static char	*read_until_nl(int fd, char *lines)
{
	char	*buffer;
	int		bytes;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{
		free(lines);
		return (NULL);
	}
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (!reflect_lines(bytes, &buffer, &lines, fd))
		return (NULL);
	return (lines);
}

static char	*extract_current_line(char *lines)
{
	char	*current_line;
	int		i;

	i = 0;
	while (lines[i] && lines[i] != '\n')
		i++;
	if (lines[i] == '\n')
		i++;
	current_line = ft_strndup(lines, i);
	if (!current_line)
	{
		return (NULL);
	}
	return (current_line);
}

static char	*update_lines(char *lines)
{
	char	*next_lines;
	char	*tmp;

	next_lines = ft_strchr(lines, '\n');
	if (!next_lines)
	{
		free(lines);
		return (NULL);
	}
	if (*(next_lines + 1) == '\0')
	{
		free(lines);
		return (NULL);
	}
	tmp = ft_strndup(next_lines + 1, ft_strlen(next_lines + 1));
	free(lines);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*lines;
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(lines);
		lines = NULL;
		return (NULL);
	}
	lines = read_until_nl(fd, lines);
	if (!lines)
		return (NULL);
	current_line = extract_current_line(lines);
	if (!current_line)
	{
		free(lines);
		lines = NULL;
		return (NULL);
	}
	lines = update_lines(lines);
	return (current_line);
}
