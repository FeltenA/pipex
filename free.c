/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:30:34 by afelten           #+#    #+#             */
/*   Updated: 2022/09/17 17:54:31 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	free_split(char **split);
void	close_pipes(t_data *data);

void	free_data_err_p(t_data *data)
{
	free_split(data->path);
	close(data->fd1);
	close(data->fd2);
	if (data->here_doc)
		unlink(".infile_tmp");
	perror("Pipe: ");
	exit(1);
}

void	free_data_err(t_data *data)
{
	free_split(data->path);
	close(data->fd1);
	close(data->fd2);
	if (data->here_doc)
		unlink(".infile_tmp");
	close_pipes(data);
	free(data->pipe);
	exit(1);
}

void	free_data(t_data *data)
{
	free_split(data->path);
	close_pipes(data);
	free(data->pipe);
	close(data->fd1);
	close(data->fd2);
	if (data->here_doc)
		unlink(".infile_tmp");
}