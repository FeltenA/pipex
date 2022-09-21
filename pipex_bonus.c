/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:54:35 by afelten           #+#    #+#             */
/*   Updated: 2022/09/17 17:56:24 by afelten          ###   ########.fr       */
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
int		ft_strcmp(const char *s1, const char *s2);
char	**get_path(char **envp);
void	child_proc(char *cmd, t_data *data, int id);
void	free_split(char **split);
int		open_files(int argc, char *argv[], t_data *data);
void	free_data_err_p(t_data *data);
void	free_data_err(t_data *data);
void	free_data(t_data *data);
void	err_msg_exit(char *msg);

void	close_pipes(t_data *data)
{
	int	i;
	int	nbpipe;

	i = -1;
	nbpipe = (data->nbcmd - 1) * 2;
	while (++i < nbpipe)
		close(data->pipe[i]);
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

int	pipex(char **cmd, t_data *data)
{
	pid_t	proc;
	int		i;

	i = -1;
	while (++i < data->nbcmd)
	{
		proc = fork();
		if (proc < 0)
		{
			perror("Fork: ");
			free_data_err(data);
		}
		if (!proc)
			child_proc(cmd[i + 2 + data->here_doc], data, i);
	}
	close_pipes(data);
	waitpid(-1, 0, 0);
	return (1);
}

int	main(int argc, char *argv[], char **envp)
{
	t_data	data;

	if (!envp[0])
		err_msg_exit("Environment variable not present\n");
	if (argc < 5)
		err_msg_exit("Not enough arguments\n");
	if (!ft_strcmp(argv[1], "here_doc"))
		data.here_doc = 1;
	else
		data.here_doc = 0;
	open_files(argc, argv, &data);
	data.envp = envp;
	data.path = get_path(envp);
	data.nbcmd = argc - 3 - data.here_doc;
	data.pipe = malloc(sizeof(int) * (data.nbcmd - 1) * 2);
	if (!data.pipe || !create_pipes(&data))
		free_data_err_p(&data);
	pipex(argv, &data);
	free_data(&data);
	return (0);
}
