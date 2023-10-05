/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:17:37 by cofoundo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/28 22:28:34 by cofoundo         ###   ########.fr       */
=======
/*   Updated: 2023/03/21 22:35:04 by cofoundo         ###   ########.fr       */
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_args
{
	char	*str;
	int		i;
	int		i_max;
}	t_args;

typedef struct s_data
{
	char	***parse;
	char	*cmd;
	int		parse_i;
	int		parse_j;
	int		parse_k;
}	t_data;

typedef struct s_history
{
	char	**str;
	int		i;
}	t_history;

typedef struct s_history
{
    char    **str;
    int     i;
}   t_history;

#endif
