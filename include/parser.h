/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:45:26 by cofoundo          #+#    #+#             */
/*   Updated: 2023/03/31 11:01:45 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "structure.h"

char    **cpy_parse_j(t_data *data);
char    ***copy_parse_for_node(t_data *data);
int     add_history(t_args *args, t_history *history);
int     quote(t_args *args, t_data *data, char c);
int     parse_simple_quote(t_args *args);
int     ft_parse(t_args *args, t_data *data, t_history *history);
int     add_command(t_data *data, char *str);
int     parse_node(t_args *args, t_data *data);
int     add_node(t_data *data, char *str, int i);
int     ft_cmp(char *str, int i, char c);
int	    ft_strcmpr(t_args *args, char *check);
int     parse_built_int(t_args *args, t_data *data);
int     parse_echo(t_args *args);
void    skip_white_space(t_args *args);
void    add_until_space(t_args *args);
char    *cpy_str(t_data *data, int i, int j);
char	*ft_strjoin(char *s1, char *s2);
int     start_expance(t_args *args, char c, int k);
int     parse_quote(t_args *args, char c);
int     parse_built_in(t_args *args, t_data *data);
#endif