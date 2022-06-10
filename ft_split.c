/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:13:12 by afelten           #+#    #+#             */
/*   Updated: 2022/05/02 18:15:22 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_str_num(char const *s, char c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			num++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (num);
}

static char	*cpy_str(const char **s, char c)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (**s && **s != c)
	{
		str[i] = **s;
		(*s)++;
		i++;
	}
	str[i] = 0;
	return (str);
}

static void	free_funct(char **sstr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(sstr[i]);
		i++;
	}
	free(sstr);
}

char	**ft_split(char const *s, char c)
{
	char	**sstr;
	int		j;

	sstr = malloc((get_str_num(s, c) + 1) * sizeof(char *));
	if (!sstr)
		return (0);
	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			sstr[j] = cpy_str(&s, c);
			if (!sstr[j])
			{
				free_funct(sstr, j);
				return (0);
			}
			j++;
		}
		else
			s++;
	}
	sstr[j] = 0;
	return (sstr);
}
