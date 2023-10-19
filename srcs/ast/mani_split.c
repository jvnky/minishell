/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mani_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:42:07 by ychair            #+#    #+#             */
/*   Updated: 2023/10/19 04:32:09 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ft_count(char const *s, char c)
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
	if (s[i - 1] == c)
		j++;
	return (j);
}

static char	*ft_alloc(char const *s, char c)
{
	char	*dst;
	int		i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i] = '\0';
	i -= 1;
	while (i >= 0)
	{
		dst[i] = s[i];
		i--;
	}
	return (dst);
}

char	**ft_end(char **dst, int j)
{
	dst[j] = '\0';
	return (dst);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**dst;

	if (s)
	{
		i = 0;
		j = -1;
		dst = malloc(sizeof(char *) * (ft_count(s, c) + 1));
		if (!dst)
			return (NULL);
		while (s[i])
		{
			dst[++j] = ft_alloc(&s[i], c);
			k = -1;
			while (s[i] && dst[j][++k] && s[i] == dst[j][k])
				i++;
		}
		return (ft_end(dst, ++j));
	}
	return (NULL);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array[i]);
	free(array);
	array = NULL;
}
