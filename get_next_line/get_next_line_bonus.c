/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arosinsk <arosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:32:50 by arosinsk          #+#    #+#             */
/*   Updated: 2024/06/27 20:47:56 by arosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file_to_buffer(char *buffer, int fd)
{
	char	*temp;
	int		bytes;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (0);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			if (buffer)
				free(buffer);
			free(temp);
			return (NULL);
		}
		temp[bytes] = '\0';
		buffer = ft_strjoin_gnl_edition(buffer, temp);
	}
	free(temp);
	return (buffer);
}

static char	*load_buffer_into_line(char *buffer)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!buffer[i])
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i] = '\0';
	while (--i + 1)
		str[i] = buffer[i];
	return (str);
}

char	*refresh_buffer(char *buffer)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!buffer)
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (0);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!str)
		return (0);
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buffer[fd] = read_file_to_buffer(buffer[fd], fd);
	if (!buffer[fd])
		return (0);
	line = load_buffer_into_line(buffer[fd]);
	buffer[fd] = refresh_buffer(buffer[fd]);
	return (line);
}
//  #include <stdio.h>

// int	main(void)
// {
// 	char *str4 = 0;
// 	int fd = open("test.txt", O_RDONLY);
// 	for (int a = 0; a < 140; a++)
// 	{
// 		str4 = get_next_line(fd);
// 		if (str4 == NULL)
// 		{
// 			printf("	NULL	\n");
// 			break ;
// 		}
// 		printf("%s", str4);
// 		free(str4);
// 	}
// 	close(fd);
// }