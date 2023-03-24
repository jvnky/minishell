/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:01:32 by cofoundo          #+#    #+#             */
/*   Updated: 2023/03/22 01:31:34 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int reset_env(char *buff, int i, char **env)
// {
//     int j;

//     j = -1;
//     while (buff[++j])
//         ;
//     free(env[i]);
//     env[i] = malloc(sizeof(char) * (j + 1));
//     if (!env[i])
//         return (-1);
//     env[i][j] = '\0';
//     while (--j >= 0)
//         env[i][j] = buff[j];
//     return (0);
// }

// int env_value(char *str, char **env)
// {
//     int i;
//     int j;

//     i = -1;
//     while(env[++i])
//     {
//         j = -1;
//         while(env[i][++j] == str[j])
//             ;
//         if(!str[j] && !env[i][j])
//             return (i);
//     }
//     return (-1);
// }

// char    *ft_strcpy(char *dst, char *src)
// {
//     int i;

//     i = -1;
//     while(srcs[++i])
//         dst[i] = srcs[i];
//     dst[i] = '\0';
//     return (dst);
// }
