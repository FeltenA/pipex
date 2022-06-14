/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:54:35 by afelten           #+#    #+#             */
/*   Updated: 2022/06/14 15:56:10 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
char	**get_path(char **envp);
void	child_proc(char *cmd, t_data *data, int id);
void	free_split(char **split);

void	close_pipes(t_data *data)
{
	int	i;
	int	nbpipe;

	i = -1;
	nbpipe = (data->nbcmd - 1) * 2;
	while (++i < nbpipe)
		close(data->pipe[i]);
}

void	free_data(t_data *data)
{
	free_split(data->path);
	close_pipes(data);
	free(data->pipe);
	close(data->fd1);
	close(data->fd2);
}

int	pipex(char **cmd, t_data *data)
{
	pid_t	proc;
	int		i;

	i = -1;
	while (++i < data->nbcmd)
	{
		proc = fork();
		if (proc < 0)
			return (0);
		if (!proc)
			child_proc(cmd[i + 2], data, i);
	}
	close_pipes(data);
	waitpid(-1, 0, 0);
	return (1);
}

int	create_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbcmd - 1)
	{
		if (pipe(data->pipe + 2 * i) < 0)
			return (0);
		i++;
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
		here_doc_infile(data);
	else
		data->fd1 = open(argv[1], O_RDONLY);
}

int	main(int argc, char *argv[], char **envp)
{
	t_data	data;

	if (argc < 5)
		return (1);
	if (ft_strcmp(argv[1], "here_doc"))
		data->here_doc = 1;
	else
		data->here_doc = 0;
	data.fd1 = open(argv[1], O_RDONLY);
	data.fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data.fd1 < 0 || data.fd2 < 0)
		return (1);
	data.envp = envp;
	data.path = get_path(envp);
	if (!data.path)
		return (1);
	data.nbcmd = argc - 3;
	data.pipe = malloc(sizeof(int) * (data.nbcmd - 1) * 2);
	if (!data.pipe)
		return (0);
	create_pipes(&data);
	pipex(argv, &data);
	free_data(&data);
}
