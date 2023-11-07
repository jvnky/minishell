/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lovenorm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 01:19:25 by ychair            #+#    #+#             */
/*   Updated: 2023/10/24 01:21:36 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	free_splith_head(char *path, char **path_split)
{
	free(path);
	free_array(path_split);
}

char	*set_path_i(char *path_split, char *cmd)
{
	char	*road;

	road = ft_strjoin(path_split, "/");
	free(path_split);
	path_split = ft_strjoin(road, cmd);
	free(road);
	return (path_split);
}

char	*set_cmd(char **cmd)
{
	if (cmd[0][0] == '\'' || cmd[0][0] == '\"')
		cmd[0] = chekg(cmd[0]);
	return (cmd[0]);
}

char	*set_road(char **path_split, char *path, int i)
{
	char	*road;

	road = NULL;
	road = truecpy(path_split[i]);
	free_splith_head(path, path_split);
	return (road);
}

char	*get_absolute_path(char **cmd, char **env, int i)
{
	char	*path;
	char	**path_split;

	cmd[0] = set_cmd(cmd);
	path = NULL;
	path = cd_option_utils(env, path, "PATH");
	if (!path)
		return (NULL);
	path_split = ft_splitpath(path, ':');
	while (path_split[++i])
	{
		path_split[i] = set_path_i(path_split[i], cmd[0]);
		if (!path_split[i])
		{
			free_splith_head(path, path_split);
			return (NULL);
		}
		if (access(path_split[i], F_OK) == 0)
			return (set_road(path_split, path, i));
	}
	free_splith_head(path, path_split);
	return (NULL);
}
