/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:04:29 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/07 00:17:52 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(char **env, int fd)
{
    int i;
    
    i = -1;
    while (env[++i])
        ft_echo(env[i], 0, fd);
    return (0);
}
