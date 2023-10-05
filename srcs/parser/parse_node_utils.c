/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:23:45 by cofoundo          #+#    #+#             */
/*   Updated: 2023/08/28 23:28:52 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expance_pipe(t_args *args, int k)
{
	char	*tmp;
	char	*dst;
	size_t	n;
	int		i;

	n = 64;
	while (k == 0)
	{
		i = 0;
		write(1, "pipe> ", 6);
		getline(&tmp, &n, stdin);
		while (tmp[i])
			i++;
		if (tmp[i])
			k++;
		dst = ft_strjoin(args->str, tmp);
		if (!dst == 0)
			return (0);
		free(args->str);
		args->str = dst;
	}
	return (1);
}

int	check_fill(t_args *args)
{
	int	i;

	i = args->i + 1;
	while (args->str[i] && (args->str[i] == ' '
			|| args->str[i] == '\t'
			|| args->str[i] == '\n' || args->str[i] == '\r'
			|| args->str[i] == '\v'
			|| args->str[i] == '\f'))
		i++;
	if (!args->str[i])
		return (0);
	else
		return (1);
}
