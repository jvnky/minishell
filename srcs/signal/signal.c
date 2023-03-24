/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:17:51 by cofoundo          #+#    #+#             */
/*   Updated: 2023/02/24 00:50:01 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_kill(int signal)
{
    (void)signal;
    //free_all();
    exit(ernno);
}

void    press_c(int signal)
{
    (void)signal;
    write(1, "\n", 1);
    
    //trouver un moyen de juste retourner au debut du main
}

void    start_signal()
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, press_c);
} 