/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:18:37 by cofoundo          #+#    #+#             */
/*   Updated: 2021/10/07 17:45:39 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_split(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (s2[i])
		i = -1;
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dst;
	int		j;

	i = ft_strlen(s1);
	j = 0;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i] = 0;
	while (j < i)
	{
		dst[j] = s1[j];
		j++;
	}
	return (dst);
}
