/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:51:06 by ychair            #+#    #+#             */
/*   Updated: 2023/10/19 01:22:05 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

char	*chekg(char *src)
{
	int		i;
	char	*dst;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	if (i == 2 || i == 0)
		return (NULL);
	dst = malloc(sizeof(char) * i - 1);
	dst[i - 2] = '\0';
	while ((i - 2) > 0)
	{
		dst[i - 3] = src[i - 2];
		i--;
	}
	return (dst);
}


char	*nospace(char *src, char **env)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	dst = ft_split(src, '\n');
	if (!dst)
		return (NULL);
	while (dst[i])
	{
		j = -1;
		while (dst[i][++j] && dst[i][j] != '$')
			;
		if (dst[i][j] && dst[i][j] == '$')
		{
			dst[i] = find_env(dst[i], j, env);
			i++;
		}
		else
			i++;
	}
	src = new_src(dst, i, src);
	if (!src)
		return (NULL);
	return (src);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
