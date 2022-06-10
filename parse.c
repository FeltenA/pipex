/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:31:07 by afelten           #+#    #+#             */
/*   Updated: 2022/06/10 13:32:54 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

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
			i = -1;
			while (path[++i])
			{
				save = path[i];
				path[i] = ft_strjoin(path[i], "/");
				free(save);
			}
			return (path);
		}
		i++;
	}
	return (0);
}
