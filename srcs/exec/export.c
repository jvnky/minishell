/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 02:42:15 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/25 02:11:00 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cpy_env(char **env, int i)
{
	char	*str;
	int		j;

	j = -1;
	while (env[i][++j])
		;
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	str[j] = '\0';
	while (--j >= 0)
		str[j] = env[i][j];
	return (str);
}

static char	*put_new_env(char *str)
{
	char	*dst;
	int		j;

	j = -1;
	while (str[++j])
		;
	dst = malloc(sizeof(char) * (j + 1));
	if (!dst)
		return (NULL);
	dst[j] = '\0';
	while (--j >= 0)
		dst[j] = str[j];
	return (dst);
}

char	**ft_export(char **env, char *str)
{
	char	**dst;
	int		i;

	i = -1;
	while (env[++i])
		;
	dst = malloc(sizeof(char *) * (i + 2));
	if (!dst)
		return (NULL);
	dst[i + 1] = '\0';
	i = -1;
	while (env[++i])
	{
		dst[i] = cpy_env(env, i);
		if (!dst[i])
			return (NULL);
	}
	dst[i] = put_new_env(str);
	if (!dst[i])
		return (NULL);
	free_env(env);
	return (dst);
}
