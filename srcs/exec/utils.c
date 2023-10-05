/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:01:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/20 22:21:59 by ychair           ###   ########.fr       */
=======
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:01:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/06/22 01:20:22 by cofoundo         ###   ########.fr       */
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int reset_env(char *buff, int i, char **env)
{
    int j;

    j = -1;
    while (buff[++j])
        ;
    free(env[i]);
    env[i] = malloc(sizeof(char) * (j + 1));
    if (!env[i])
        return (-1);
    env[i][j] = '\0';
    while (--j >= 0)
        env[i][j] = buff[j];
    return (0);
}

int env_value(char **env, char *str)
{
    int i;
    int j;
    
    i = -1;
    while(env[++i])
    {
        j = 0;
        while(env[i][j] == str[j])
            j++;
<<<<<<< HEAD
        if(!str[j])
=======
        if(!str[j] && !env[i][j])
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
            return (i);
    }
    return (-1);
}

char    *ft_strcpy(char *dst, char *src)
{
    int i;
    
    i = -1;
    while(src[++i])
        dst[i] = src[i];
    dst[i] = '\0';
    return (dst);
}