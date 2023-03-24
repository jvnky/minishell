/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:17:37 by cofoundo          #+#    #+#             */
/*   Updated: 2023/02/24 22:52:32 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_args
{
    char        *str;
    int         i;
    int         i_max;
}   t_args;

typedef struct  s_data
{
    char    ***parse;
    char    *cmd;
    int parse_i;
    int parse_j;
    int parse_k;
}   t_data;

#endif
