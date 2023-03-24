/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:43:23 by cofoundo          #+#    #+#             */
/*   Updated: 2023/02/17 22:18:55 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	j = -1;
	while (s2[++j])
		dst[++i - 1] = s2[j];
	dst[i] = '\0';
	return (dst);
}

int check_white_space(t_args *args, int i)
{
	if (args->str[i] && (args->str[i] == ' ' || args->str[i] == '\t' 
				|| args->str[i] == '\n' || args->str[i] == '\r' || args->str[i] == '\v' 
				|| args->str[i] == '\f'))
		return (1);
	else
		return (0);
}

int add_rest(t_args *args, t_data *data)
{
	int i;
	int j;
	char    *tmp;
	
	if (check_white_space(args, args->i) == 1)
		return (1);
	i = args->i;
	while (args->str[i] && check_white_space(args, i) == 0 && args->str[i] != '|')
		i++;
	tmp = malloc(sizeof(char) * (i - args->i + 1));
	if (!tmp)
		return (0);
	tmp[i - args->i] = '\0';
	j = i;
	i--;
	while ((i - args->i) >= 0)
	{
		tmp[i - args->i]  = args->str[i];
		i--;
	}
	if (add_command(data, tmp) == 0)
		return (0);
	args->i = j;
	return (1);
}

int start_expance(t_args *args, char c)
{
	char    *tmp;
	char    *dst;
	size_t  n;
	int     k;
	int     i;
	
	n = 64;
	k = 0;
	while (k == 0)
	{
		i = 0;
		if (c == '\"')
			write(1, "dquote> ", 8);
		else
			write(1, "quote> ", 7);
		getline(&tmp, &n, stdin);
		while(tmp[i] && tmp[i] != c)
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

int parse_expance(t_args *args, t_data *data, char c)
{
	if (ft_cmp(args->str, args->i, c) != 0)
	{
		if (parse_quote(args, c) == 1)
		{
			if (quote(args, data, c) == 0)
				return (0);
		}
		else
		{
			if (start_expance(args, c) == 0)
				return (0);
			if (quote(args, data, c) == 0)
				return (0);
		}
	}
	return (1);
}

int ft_parse(t_args *args, t_data *data)
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
	return (1);
}
