/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:45:26 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/14 00:47:13 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structure.h"

char	***copy_parse_for_node(t_data *data, int i, int j);

char	**cpy_parse_j(t_data *data, int i);

char	*cpy_str(t_data *data, int i, int j);
char	*ft_strjoin(char *s1, char *s2);

int		add_command(t_data *data, char *str, int i);
int		add_node(t_data *data, char *str, int i);
int		check_fill(t_args *args);
int		check_white_space(t_args *args, int i);
int		expance_pipe(t_args *args, int k);
int		ft_cmp(char *str, int i, char c);
int		ft_parse(t_args *args, t_data *data);
int		ft_strcmpr(t_args *args, char *check);
int		parse_built_int(t_args *args, t_data *data);
int		parse_built_in(t_args *args, t_data *data);
int		parse_echo(t_args *args);
int		parse_expance(t_args *args, t_data *data, char c);
int		parse_node(t_args *args, t_data *data);
int		parse_quote(t_args *args, char c);
int		parse_simple_quote(t_args *args);
int		quote(t_args *args, t_data *data, char c, int k);
int		start_expance(t_args *args, char c, int k);

void	skip_white_space(t_args *args);
void	add_until_space(t_args *args);
#endif
