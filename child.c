/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:41:17 by afelten           #+#    #+#             */
/*   Updated: 2022/06/14 15:10:22 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	close_pipes(t_data *data);

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

void	child_proc(char *cmd, t_data *data, int id)
{
	char	**splt_cmd;
	char	*exec;
	int		i;

	splt_cmd = ft_split(cmd, ' ');
	if (!splt_cmd)
		exit(0);
	connect_fd(data, id);
	close_pipes(data);
	i = -1;
	while (data->path[++i])
	{
		exec = ft_strjoin(data->path[i], splt_cmd[0]);
		if (!exec)
			exit(0);
		execve(exec, splt_cmd, data->envp);
		free(exec);
	}
}
