#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s);
int	ft_strcmp(const char *s1, const char *s2);

static int	here_doc_infile(t_data *data, char *argv[])
{
	char	*line;
	int	fd;

	fd = open(".infile_tmp", O_CREAT | O_WRONLY | O_TRUNC);
	if (!fd)
		return (0);
	while (1)
	{
		write(1, "heredoc>", 9);
		line = get_next_line(0);
		if (!line)
			return (0);
		write(fd, line, ft_strlen(line));
		if (!ft_strcmp(line, argv[2]))
			break ;
	}
	close(fd);
	data->fd1 = open(".infile_tmp", O_RDONLY);
	if (data->fd1 < 0)
	{
		unlink(".infile_tmp");
		return (0);
	}
	return (1);
}

int	open_files(int argc, char *argv[], t_data *data)
{
	if (data->here_doc)
		data->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		data->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (data->fd2 < 0)
		return (0);
	if (data->here_doc)
		here_doc_infile(data, argv);
	else
		data->fd1 = open(argv[1], O_RDONLY);
}