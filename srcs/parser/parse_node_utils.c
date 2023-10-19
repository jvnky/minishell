/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:23:45 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/19 02:38:57 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expance_pipe(t_args *args, int k)
{
	char	*tmp;
	char	*dst;
	size_t	n;

	(void)k;
	n = 0;
	write(1, "pipe> ", 6);
	getline(&tmp, &n, stdin);
	if (tmp)
	{
		dst = ft_strjoin(args->str, tmp);
		if (!dst)
			return (0);
		free(args->str);
		free(tmp);
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
