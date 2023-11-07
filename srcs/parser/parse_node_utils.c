/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:23:45 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/25 23:37:59 by cofoundo         ###   ########.fr       */
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
	free_data(data);
	data->parse = dst;
	data->parse_i = i;
	return (1);
}

char	***copy_parse_for_node(t_data *data, int i, int j)
{
	char	***dst;

	dst = malloc(sizeof(char **) * (data->parse_i + 3));
	if (!dst)
		return (NULL);
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
