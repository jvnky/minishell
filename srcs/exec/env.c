/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:04:29 by cofoundo          #+#    #+#             */
/*   Updated: 2023/03/10 22:16:56 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(char *str, char **env, int fd)
{
    int i;
    
    if (str)
        return (-1);
    i = -1;
    while (env[++i])
        ft_echo(env[i], 0, fd);
    return (0);
}