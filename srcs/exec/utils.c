/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:01:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/15 01:48:57 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**reset_env(char *buff, int i, char **env)
{
	int	j;

	j = -1;
	while (buff[++j])
		;
	free(env[i]);
	env[i] = malloc(sizeof(char) * (j + 1));
	if (!env[i])
		return (NULL);
	env[i][j] = '\0';
	while (--j >= 0)
		env[i][j] = buff[j];
	return (env);
}

int	env_value(char **env, char *str)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] == str[j])
			j++;
		if (!str[j])
			return (i);
	}
	return (-1);
}

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

int	ft_strcompr(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}
