/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:34:28 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/25 23:51:53 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_two(char *path, char *dst)
{
	free(path);
	free(dst);
}

static void	print_new_path(char *str, char *path)
{
	free(path);
	path = NULL;
	g_ret_number = 1;
	write(2, "minishell: cd:", 14);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 29);
}

static char	**new_path(char **env, char *path, char *str)
{
	char	*dst;

	if (chdir(str) == -1)
	{
		print_new_path(str, path);
		return (env);
	}
	dst = ft_strjoin("OLDPWD=", path);
	if (!dst)
		return (NULL);
	env = reset_env(dst, env_value(env, "OLDPWD"), env);
	if (!env || !str)
		return (NULL);
	free_two(path, dst);
	path = malloc(sizeof (char) * (PATH_MAX + 1));
	if (!path)
		return (NULL);
	path = getcwd(path, PATH_MAX);
	dst = ft_strjoin("PWD=", path);
	env = reset_env(dst, env_value(env, "PWD"), env);
	if (!env)
		return (NULL);
	free_two(path, dst);
	return (env);
}

static char	**not_str(char **env, char *path)
{
	env = cd_home(env, path);
	free(path);
	return (env);
}

char	**ft_cd(char *str, char **env)
{
	char	*path;
	int		i;

	path = malloc(sizeof (char) * (PATH_MAX + 1));
	path = getcwd(path, PATH_MAX);
	if (!str)
		return (not_str(env, path));
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
		path = NULL;
	}
	else
		env = new_path(env, path, str);
	if (!env)
		return (NULL);
	return (env);
}
