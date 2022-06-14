/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:31:07 by afelten           #+#    #+#             */
/*   Updated: 2022/06/14 12:23:55 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**add_slash(char **path)
{
	char	*save;
	int		i;

	i = 0;
	while (path[i])
	{
		save = path[i];
		path[i] = ft_strjoin(path[i], "/");
		if (!(path[i]))
		{
			free_split(path);
			return (0);
		}
		free(save);
		i++;
	}
	return (path);
}

char	**get_path(char **envp)
{
	char	**path;
	char	*save;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				return (0);
			return (add_slash(path));
		}
		i++;
	}
	return (0);
}
