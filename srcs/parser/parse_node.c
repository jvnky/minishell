/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:56:27 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/25 23:41:15 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirec_utils(t_data *data, char *dst)
{
	if (!data->parse[0])
		add_command(data, dst, 0);
	else if (add_node(data, dst, 0) == 0)
		return (0);
	return (1);
}

static int	parse_redirec(t_args *args, t_data *data, char c)
{
	char	dst[3];

	if (args->str[args->i] == c)
	{
		if (args->str[args->i + 1] && args->str[args->i + 1] == c)
		{
			dst[2] = '\0';
			dst[0] = c;
			dst[1] = c;
			if (redirec_utils(data, dst) == 0)
				return (0);
			args->i += 2;
		}
		else
		{
			dst[1] = '\0';
			dst[0] = c;
			if (!data->parse[0])
				add_command(data, dst, 0);
			else if (add_node(data, dst, 0) == 0)
				return (0);
			args->i++;
		}
	}
	return (1);
}

static int	check_fill_pipe(t_args *args)
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
	else if (args->str[i] == '|')
		return (2);
	else
		return (1);
}

int	parse_node(t_args *args, t_data *data)
{
	int	check;

	if (args->str[args->i] == '|')
	{
		check = check_fill_pipe(args);
		if (!data->parse[0])
			check = 2;
		while (check == 0)
		{
			if (expance_pipe(args, 0) == 0)
				return (0);
			check = check_fill_pipe(args);
		}
		if (check == 2)
			return (0);
		if (add_node(data, "|", 0) == 0)
			return (0);
		args->i++;
	}
	else if (parse_redirec(args, data, '<') == 0)
		return (0);
	else if (parse_redirec(args, data, '>') == 0)
		return (0);
	return (1);
}
