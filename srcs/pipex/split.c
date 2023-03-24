/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 20:14:23 by cofoundo          #+#    #+#             */
/*   Updated: 2021/09/10 20:15:10 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_alloc(char *s, char c)
{
	char	*dst;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i] = '\0';
	i -= 1;
	while (i >= 0 && s[i] != c)
	{
		dst[i] = s[i];
		i--;
	}
	return (dst);
}

static int	ft_count(char const *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (s[0] != c)
		j++;
	while (s[i])
	{
		while (s[i] == c && s[i])
		{
			i++;
			if (s[i] != c && s[i])
			{
				j++;
				while (s[i] != c && s[i])
					i++;
			}
		}
		if (s[i])
			i++;
	}
	return (j);
}

char	**ft_split(char *s, char c)
{
	int		i[2];
	char	**dst;

	if (s)
	{
		i[0] = 0;
		i[1] = -1;
		dst = malloc(sizeof(char *) * (ft_count(s, c) + 1));
		if (!dst)
			return (NULL);
		while (s[i[0]])
		{
			while (s[i[0]] && s[i[0]] == c)
				i[0]++;
			if (s[i[0]] && s[i[0]] != c)
			{
				dst[++i[1]] = ft_alloc(&s[i[0]], c);
				while (s[i[0]] && s[i[0]] != c)
					i[0]++;
			}
		}
		dst[++i[1]] = NULL;
		return (dst);
	}
	return (NULL);
}
