/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:53:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/03/12 00:15:20 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void free_env(char **env)
{
    int i;
    
    i = -1;
    while (env[++i])
        free(env[i]);
    free(env);
}

int ft_unset(char *args, char **env)
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
        return (-1);
    dst[i - 1] = '\0';
    k = env_value(str, env);
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
                return (-1);
            dst[x][j] = '\0';
            while (--j >= 0)
                dst[x][j] = env[i][j]
            x++;
        }
    }
    free_env(env);
    env = dst;
    return (0);
}