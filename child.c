/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:41:17 by afelten           #+#    #+#             */
/*   Updated: 2022/06/16 16:25:40 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	close_pipes(t_data *data);
void	msg_error_cmd(char *cmd);
void	free_split(char **split);

void	free_child(t_data *data)
{
	free_split(data->path);
	free(data->pipe);
	exit(1);
}

void	connect_fd(t_data *data, int id)
{
	if (id == 0)
	{
		dup2(data->fd1, 0);
		dup2(data->pipe[1], 1);
	}
	else if (id == data->nbcmd - 1)
	{
		dup2(data->pipe[id * 2 - 2], 0);
		dup2(data->fd2, 1);
	}
	else
	{
		dup2(data->pipe[id * 2 - 2], 0);
		dup2(data->pipe[id * 2 + 1], 1);
	}
}

static int	get_index_path(char *cmd, t_data *data)
{
	char	*fcmd;
	int		i;

	i = -1;
	while (data->path[++i])
	{
		fcmd = ft_strjoin(data->path[i], cmd);
		if (!fcmd)
			return (-1);
		if (!access(fcmd, 0))
		{
			free(fcmd);
			return (i);
		}
		free(fcmd);
	}
	return (-1);
}

void	child_proc(char *cmd, t_data *data, int id)
{
	char	**splt_cmd;
	char	*exec;
	int		i;

	splt_cmd = ft_split(cmd, ' ');
	if (!splt_cmd)
		free_child(data);
	connect_fd(data, id);
	close_pipes(data);
	i = get_index_path(splt_cmd[0], data);
	if (i >= 0)
	{
		exec = ft_strjoin(data->path[i], splt_cmd[0]);
		if (!exec)
		{
			free_split(splt_cmd);
			free_child(data);
		}
		execve(exec, splt_cmd, data->envp);
	}
	msg_error_cmd(splt_cmd[0]);
	free_split(splt_cmd);
	free_child(data);
}
