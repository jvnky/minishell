/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:34:28 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/19 22:55:15 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int new_path(char *path, int i, char **env)
{
    char *buff;
    if (i == 0)
    {
        buff = ft_strjoin("OLDPWD=", path);
        if (reset_env(buff, env_value(env, "OLDPWD"), env) == -1)
            return(-1);
        free(buff);
        getcwd(path, PATH_MAX);
        buff = ft_strjoin("PWD=", path);
        if (reset_env(buff, env_value(env, "PWD"), env) == -1)
            return (-1);
        free(buff);
    }
    return (0);
 }

int actual_path(char *str, char **env)
{
    int i;
    int j;

    if (!str || (str[0] == '~' || !str[1]))
    {
        j = env_value(env, "HOME");
        i = chdir(env[j]);
        if (i == -1)
            return (-1);
        return (i);
    }
    return (0);
}

int recup_path(char *str, char *buff, char **env)
{
    int i;

    i = actual_path(str, env);
    if (i == 0)
    {
        if (!(ft_strncmp(str, "~root", 5) == 1))
            str[0] = '/';
        if (str[0] == '~')
        {
            ft_strcpy(buff, "/homes/");
            ft_strcpy(buff + 7, env[env_value(env, "USER")]);
        }
        else
            ft_strcpy(buff, str);
        i = chdir(buff);
        if (i == -1)
            return (0);
    }
    return (i);
}

int ft_cd(char *str, char **env)
{
    int i;
    char    path[PATH_MAX];
    char    buff[PATH_MAX];
    puts("bouuuu");
    getcwd(path, PATH_MAX);
    i = recup_path(str, buff, env);
    new_path(path, i, env);
    return (i);
}
