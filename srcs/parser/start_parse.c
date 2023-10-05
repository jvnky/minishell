/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:43:23 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/05 23:10:33 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_rest(t_args *args, t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	if (check_white_space(args, args->i) == 1)
		return (1);
	i = args->i;
	while (args->str[i] && check_white_space(args, i) == 0
		&& args->str[i] != '|')
		i++;
	tmp = malloc(sizeof(char) * (i - args->i + 1));
	if (!tmp)
		return (0);
	tmp[i - args->i] = '\0';
	j = i;
	i--;
	while ((i - args->i) >= 0)
	{
		tmp[i - args->i] = args->str[i];
		i--;
	}
	if (add_command(data, tmp, 0) == 0)
		return (0);
	args->i = j;
	return (1);
}

int	ft_parse(t_args *args, t_data *data, t_history *history)
{
	data->parse_i = 0;
	while (args->str[args->i])
	{
		data->parse_j = 0;
		data->parse_k = 0;
		if (parse_node(args, data) == 0)
			return (0);
		else if (parse_built_in(args, data) == 0)
			return (0);
		else if (parse_expance(args, data, '\"') == 0)
			return (0);
		else if (parse_expance(args, data, '\'') == 0)
			return (0);
		else if (add_rest(args, data) == 0)
			return (0);
		while (check_white_space(args, args->i) == 1)
			args->i++;
	}
	if (!add_history(args, history))
		return (0);
	return (1);
}
