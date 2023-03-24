/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:24:56 by cofoundo          #+#    #+#             */
/*   Updated: 2021/10/07 17:53:53 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *command, char **path_list)
{
	int		i;
	char	*dst;
	char	*tmp;

	i = -1;
	if (!command || command[0] == '/')
		return (command);
	while (path_list[++i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		if (!dst)
			return (NULL);
		dst = ft_strjoin(tmp, command);
		free(tmp);
		if (!dst)
			return (NULL);
		if (access(dst, X_OK) == 0)
			return (dst);
		free(dst);
	}
	return (command);
}

char	**all_path(char **env)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	j = 0;
	while (env[i] && ft_strcmp(env[i], "PATH=") < 0)
		i++;
	if (!env[i])
	{
		dst = malloc(sizeof(char *) * 2);
		if (!dst)
			return (NULL);
		dst[1] = NULL;
		dst[0] = ft_strdup("");
		return (dst);
	}
	while (env[i][j] != '/')
		j++;
	dst = ft_split(&env[i][j], ':');
	if (!dst)
		return (NULL);
	return (dst);
}
