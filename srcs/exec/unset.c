/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:53:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/21 01:12:30 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env(char **env)
{
    int i;
    
    i = -1;
    while (env[++i])
        free(env[i]);
    free(env);
}

char **ft_unset(char *args, char **env)
{
    int i;
    int j;
    int k;
    int x;
    char    **dst;
    
    i = -1;
    while (env[++i])
        ;
    dst = malloc(sizeof(char*) * (i));
    if (!dst)
        return (NULL);
    dst[i - 1] = '\0';
    k = env_value(env, args);
    i = -1;
    x = 0;
    while (env[++i])
    {
        if (i != k)
        {
            j = -1;
            while (env[i][++j])
                ;
            dst[x] = malloc(sizeof(char) * (j + 1));
            if (!dst[x])
                return (NULL);
            dst[x][j] = '\0';
            while (--j >= 0)
                dst[x][j] = env[i][j];//lol = lll'\0'
            x++;
        }
    }

      free_env(env);
    // free(env[k]);
    // ft_env(dst,1);
    // env = dst;
    return (dst);
}