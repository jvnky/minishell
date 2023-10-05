/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:47:09 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/05 05:08:21 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
    char *path;
    // puts("FUCK\n");
    path = getcwd(NULL, 0);
    // printf("PATH = %s\n",path);
    if (!path)
        return (1);
    else
        printf("%s\n", path);
    return (0);
}