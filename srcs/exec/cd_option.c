/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 00:02:54 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/16 22:07:04 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cd_root(char **env, char *path, char *new_path)
{
	char	*dst;

	dst = ft_strjoin("OLDPWD=", path);
	if (!dst)
		return (NULL);
	if (chdir(new_path) == -1)
		return (NULL);
	env = reset_env(dst, env_value(env, "OLDPWD"), env);
	if (!env)
		return (NULL);
	free(dst);
	dst = ft_strjoin("PWD=", new_path);
	env = reset_env(dst, env_value(env, "PWD"), env);
	if (!env)
		return (NULL);
	free(dst);
	return (env);
}

char	*cd_option_utils(char **env, char *path, char *str)
{
	int	i;
	int	j;
	int	k;

	i = env_value(env, str);
	j = -1;
	if (!env[i])
		return (NULL);
	while (env[i][++j])
		;
	k = -1;
	while (str[++k])
		;
	path = malloc(sizeof(char) * (j - k));
	if (!path)
		return (NULL);
	path[j - k - 1] = '\0';
	while ((j - k - 2) >= 0)
	{
		path[j - k - 2] = env[i][j - 1];
		j--;
	}
	return (path);
}

char	**cd_home(char **env, char *path)
{
	char	*dst;
	char	*new_path;

	dst = ft_strjoin("OLDPWD=", path);
	if (!dst)
		return (NULL);
	new_path = NULL;
	new_path = cd_option_utils(env, new_path, "HOME");
	if (chdir(new_path) == -1)
		return (NULL);
	env = reset_env(dst, env_value(env, "OLDPWD"), env);
	if (!env)
		return (NULL);
	free(dst);
	dst = ft_strjoin("PWD=", new_path);
	env = reset_env(dst, env_value(env, "PWD"), env);
	if (!env)
		return (NULL);
	free(dst);
	free(new_path);
	return (env);
}

char	**cd_minus(char **env, char *path)
{
	char	*dst;
	char	*new_path;

	dst = ft_strjoin("OLDPWD=", path);
	if (!dst)
		return (NULL);
	new_path = NULL;
	new_path = cd_option_utils(env, new_path, "OLDPWD");
	if (!new_path)
		return (NULL);
	if (chdir(new_path) == -1)
		return (NULL);
	env = reset_env(dst, env_value(env, "OLDPWD"), env);
	if (!env)
		return (NULL);
	free(dst);
	dst = ft_strjoin("PWD=", new_path);
	env = reset_env(dst, env_value(env, "PWD"), env);
	if (!env)
		return (NULL);
	free(dst);
	free(new_path);
	return (env);
}
