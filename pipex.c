/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:54:35 by afelten           #+#    #+#             */
/*   Updated: 2022/06/10 14:10:04 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

void	child_proc(int pp[2], char *cmd)
{
	char	**splt_cmd;

	splt_cmd = ft_split(cmd, " ");
	close(pp[0]);
	dup2(pp[1], 1);
	
}

int	pipex(int argc, char *argv[], char **path)
{
	
}

int	main(int argc, char *argv[], char **envp)
{
	int	fd1;
	int	fd2;
	int	i;
	int pp[2];
	pid_t	proc;

	if (argc < 5)
		return (1);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		return (1);
	dup2(fd1, 0);
	i = 1;
	while (++i < argc - 2)
	{
		pipe(pp);
		proc = fork();
		if (proc < 0)
			return (perror("Fork: "));
		if (!proc)
			child_proc(pp, argv[i]);
		close(pp[1]);
		waitpid(proc, &status, 0);
		dup2(pp[0], 1);
		close(pp[0]);
	}
}
