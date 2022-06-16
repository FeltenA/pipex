/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:45:07 by afelten           #+#    #+#             */
/*   Updated: 2022/06/16 18:16:14 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s);

void	msg_error_cmd(char *cmd)
{
	write(2, "command not found: ", 19);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}

void	err_msg_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	err_msg_exit_unlink(char *msg)
{
	write(2, msg, ft_strlen(msg));
	unlink(".infile_tmp");
	exit(1);
}
