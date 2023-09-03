/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:47:09 by cofoundo          #+#    #+#             */
/*   Updated: 2023/06/22 01:19:01 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
    char *path;
    
    path = getcwd(NULL, 0);
    if (!path)
        return (1);
    else
        printf("%s\n", path);
    return (0);
}