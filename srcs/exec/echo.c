/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:58:27 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/05 23:13:57 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(char *str, int option, int fd)
{
    write(fd, str, ft_strlen(str));
    if (option == 0)
        write(fd, "\n", 1);
    return (0);
}