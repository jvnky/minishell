/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:17:37 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/21 03:20:20 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_args
{
	char	*str;
	int		i;
	int		i_max;
	int		tout;
	int		tin;
	int		oin;
	int		oout;
	int		*fdtab;
	int		*fdtabf;
	int		jmax;
	int		imax;
}	t_args;

typedef struct s_data
{
	char	***parse;
	int		parse_i;
	int		parse_j;
	int		parse_k;
}	t_data;

typedef struct s_history
{
	char	**str;
	int		i;
}	t_history;

#endif
