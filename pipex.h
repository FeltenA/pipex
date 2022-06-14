/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:03:40 by afelten           #+#    #+#             */
/*   Updated: 2022/06/14 15:20:38 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_data
{
	char	**path;
	char	**envp;
	int		*pipe;
	int		nbcmd;
	int		fd1;
	int		fd2;
}	t_data;

#endif
