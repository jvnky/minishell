/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:34:28 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/15 02:33:35 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**new_path(char **env, char *path, char *str)
{
	char	*dst;

	dst = ft_strjoin("OLDPWD=", path);
	if (!dst)
		return (NULL);
	env = reset_env(dst, env_value(env, "OLDPWD"), env);
	if (!env || !str)
		return (NULL);
	if (chdir(str) == -1)
		return (NULL);
	free(path);
	free(dst);
	path = malloc(sizeof (char) * (PATH_MAX + 1));
	if (!path)
		return (NULL);
	path = getcwd(path, PATH_MAX);
	dst = ft_strjoin("PWD=", path);
	env = reset_env(dst, env_value(env, "PWD"), env);
	if (!env)
		return (NULL);
	free(path);
	free(dst);
	free(str);
	return (env);
}

static char	**cd_utils(char **env, char *path)
{
	char	*dst;

	dst = ft_strjoin("OLDPWD=", path);
	if (!dst)
		return (NULL);
	env = reset_env(dst, env_value(env, "OLDPWD"), env);
	if (!env)
		return (NULL);
	path = getcwd(path, PATH_MAX);
	free(dst);
	dst = ft_strjoin("PWD=", path);
	env = reset_env(dst, env_value(env, "PWD"), env);
	if (!env)
		return (NULL);
	free(dst);
	return (env);
}

static int	check_cd_option(char *str)
{
	if (ft_strcompr(str, "..") == 1)
		return (1);
	else if (ft_strcompr(str, "/") == 1)
		return (2);
	else if (ft_strcompr(str, "-") == 1)
		return (3);
	else if (ft_strcompr(str, "~") == 1 || !str)
		return (4);
	else if (ft_strcompr(str, "~root") == 1)
		return (5);
	return (0);
}

char	**launch_cd_option(char **env, char *path, int i)
{
	if (i == 1)
	{
		if (chdir("..") == -1)
			return (NULL);
		env = cd_utils(env, path);
		if (!env)
			return (NULL);
	}
	else if (i == 2)
	{
		if (chdir("/") == -1)
			return (NULL);
		env = cd_utils(env, path);
		if (!env)
			return (NULL);
	}
	else if (i == 3)
	{
		env = cd_minus(env, path);
		if (!env)
			return (NULL);
	}
	return (env);
}

char	**ft_cd(char *str, char **env)
{
	char	*path;
	int		i;

	path = malloc(sizeof (char) * (PATH_MAX + 1));
	if (!path)
		return (NULL);
	path = getcwd(path, PATH_MAX);
	i = check_cd_option(str);
	if (i != 0)
	{
		if (i >= 1 && i < 4)
			env = launch_cd_option(env, path, i);
		else if (i == 4)
			env = cd_home(env, path);
		else
			env = cd_root(env, path, "/root\0");
		free(path);
	}
	else
		env = new_path(env, path, str);
	if (!env)
		return (NULL);
	return (env);
}
