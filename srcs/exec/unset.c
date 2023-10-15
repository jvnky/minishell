/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:53:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/15 01:47:43 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}

static char	*cpy_env_prime(char **env, int i)
{
	char	*dst;
	int		j;

	j = -1;
	while (env[i][++j])
		;
	dst = malloc(sizeof(char) * (j + 1));
	if (!dst)
		return (NULL);
	dst[j] = '\0';
	while (--j >= 0)
		dst[j] = env[i][j];
	return (dst);
}

static char	**create_env(char **env)
{
	char	**dst;
	int		i;

	i = -1;
	while (env[++i])
		;
	dst = malloc(sizeof(char *) * (i));
	if (!dst)
		return (NULL);
	dst[i - 1] = '\0';
	return (dst);
}

char	**ft_unset(char *args, char **env)
{
	int		i;
	int		k;
	int		x;
	char	**dst;

	dst = create_env(env);
	if (!dst)
		return (NULL);
	k = env_value(env, args);
	i = -1;
	x = 0;
	while (env[++i])
	{
		if (i != k)
		{
			dst[x] = cpy_env_prime(env, i);
			if (!dst[x])
				return (NULL);
			x++;
		}
	}
	free_env(env);
	return (dst);
}
