/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:19:58 by afelten           #+#    #+#             */
/*   Updated: 2022/06/16 15:35:24 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_strlen(char *str);
char		*ft_strjoin_free(char *s1, char *s2);
int			isline(char *str);

void	remove_line(char **str)
{
	char	*save;
	int		i;
	int		j;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if (!(*str)[i] || !(*str)[i + 1])
	{
		free(*str);
		*str = 0;
		return ;
	}
	save = malloc((ft_strlen(*str + i + 1) + 1) * sizeof(char));
	if (!save)
		return ;
	j = 0;
	while ((*str)[++i])
	{
		save[j] = (*str)[i];
		j++;
	}
	save[j] = 0;
	free(*str);
	*str = save;
}

char	*get_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (0);
	line[i] = 0;
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	return (line);
}

char	*get_buffer(int fd)
{
	char	*buff;
	int		size;

	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (0);
	size = read(fd, buff, BUFFER_SIZE);
	if (size < 1)
	{
		free(buff);
		return (0);
	}
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	if (!save[fd])
		save[fd] = get_buffer(fd);
	if (!save[fd])
		return (0);
	while (!isline(save[fd]))
	{
		buff = get_buffer(fd);
		if (!buff)
			break ;
		save[fd] = ft_strjoin_free(save[fd], buff);
	}
	line = get_line(save[fd]);
	remove_line(&(save[fd]));
	return (line);
}
