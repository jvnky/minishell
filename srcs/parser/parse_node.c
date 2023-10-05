/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:56:27 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/02 20:52:16 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***copy_parse_for_node(t_data *data, int i, int j)
{
	char	***dst;

	dst = malloc(sizeof(char **) * (data->parse_i + 3));
	if (!dst)
		return (NULL);
	dst[data->parse_i + 1] = '\0';
	dst[data->parse_i + 2] = '\0';
	while (data->parse[++i])
	{
		j = 0;
		while (data->parse[i][j])
			j++;
		dst[i] = malloc(sizeof(char *) * (j + 1));
		if (!dst[i])
			return (NULL);
		dst[i][j] = '\0';
		j = -1;
		while (data->parse[i][++j])
		{
			dst[i][j] = cpy_str(data, i, j);
			if (dst[i][j] == NULL)
				return (NULL);
		}
	}
	return (dst);
}

int	add_node(t_data *data, char *str, int i)
{
	int		x;
	char	***dst;

	dst = copy_parse_for_node(data, -1, 0);
	if (!dst)
		return (0);
	while (data->parse[i])
		i++;
	x = 0;
	while (str[x])
		x++;
	dst[i] = malloc(sizeof(char *) * 2);
	if (!dst[i])
		return (0);
	dst[i][1] = '\0';
	dst[i][0] = malloc(sizeof(char) * (x + 1));
	if (!dst[i][0])
		return (0);
	dst[i][0][x] = '\0';
	while (--x >= 0)
		dst[i][0][x] = str[x];
	free(data->parse);
	data->parse = dst;
	data->parse_i = i;
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
			if (add_node(data, dst, 0) == 0)
				return (0);
			args->i += 2;
		}
		else
		{
			dst[1] = '\0';
			dst[0] = c;
			if (add_node(data, dst, 0) == 0)
				return (0);
			args->i++;
		}
	}
	return (1);
}

int	parse_node(t_args *args, t_data *data)
{
	if (args->str[args->i] == '|')
	{
		while (check_fill(args) == 0)
		{
			if (expance_pipe(args, 0) == 0)
				return (0);
		}
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
