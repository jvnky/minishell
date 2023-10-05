/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 02:42:15 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/07 00:21:42 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export(char **env, char *str)
{
    int i;
    int k;
    char    *flag;
    
    if (!str)
        return (-1);
    i = -1;
    while (str[++i] != '=' && str[i])
        ;
    flag = malloc(sizeof(char) * (i + 1));
    if (!flag)
        return (-1);
    flag[i] = '\0';
    while (--i >= 0)
        flag[i] = str[i];
    k = env_value(env, flag);
    if (k >= 0)
    {
        if (reset_env(str, k, env) == -1)
            return (-1);
    }
    return (0);
}