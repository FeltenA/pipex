/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:22:10 by afelten           #+#    #+#             */
/*   Updated: 2022/06/16 18:14:36 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>

void	err_msg_exit(char *msg);
void	err_msg_exit_unlink(char *msg);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);

static int	check_limiter(char *line, char *limiter)
{
	int	len_line;
	int	len_limit;

	len_line = ft_strlen(line);
	len_limit = ft_strlen(limiter);
	if (line[len_line - 1] == '\n' && len_line != len_limit + 1)
		return (1);
	return (ft_strncmp(line, limiter, len_limit));
}

static void	here_doc_infile(t_data *data, char *limiter)
{
	char	*line;
	int		fd;

	fd = open(".infile_tmp", O_CREAT | O_WRONLY | O_TRUNC);
	if (fd < 0)
		err_msg_exit("fd error\n");
	while (1)
	{
		write(1, "heredoc>", 9);
		line = get_next_line(0);
		if (!line)
			err_msg_exit_unlink("fd error\n");
		if (!check_limiter(line, limiter))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
	data->fd1 = open(".infile_tmp", O_RDONLY);
	if (data->fd1 < 0)
	{
		unlink(".infile_tmp");
		err_msg_exit("fd error\n");
	}
}

int	open_files(int argc, char *argv[], t_data *data)
{
	if (data->here_doc)
		data->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		data->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd2 < 0)
		err_msg_exit("fd error\n");
	if (data->here_doc)
		here_doc_infile(data, argv[2]);
	else
		data->fd1 = open(argv[1], O_RDONLY);
	if (data->fd1 < 0)
	{
		close(data->fd2);
		err_msg_exit("fd error\n");
	}
	return (1);
}
