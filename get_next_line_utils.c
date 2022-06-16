/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:09:42 by afelten           #+#    #+#             */
/*   Updated: 2022/05/10 13:40:46 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	tsize;
	void	*array;

	tsize = size * nmemb;
	if (size != 0 && tsize / size != nmemb)
		return (0);
	array = malloc(tsize);
	if (!array)
		return (0);
	i = -1;
	while (++i < tsize)
		*((char *)array + i) = 0;
	return (array);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (0);
	i = -1;
	while (++i < len1)
		str[i] = s1[i];
	free(s1);
	j = -1;
	while (++j < len2)
		str[i + j] = s2[j];
	free(s2);
	str[i + j] = 0;
	return (str);
}

int	isline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}
