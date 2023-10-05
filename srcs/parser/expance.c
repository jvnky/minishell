/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 21:33:41 by cofoundo          #+#    #+#             */
/*   Updated: 2023/09/05 20:34:29 by ychair           ###   ########.fr       */
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

int	check_white_space(t_args *args, int i)
{
	if (args->str[i] && (args->str[i] == ' ' || args->str[i] == '\t'
			|| args->str[i] == '\n'
			|| args->str[i] == '\r'
			|| args->str[i] == '\v'
			|| args->str[i] == '\f'))
		return (1);
	else
		return (0);
}

int	start_expance(t_args *args, char c, int k)
{
	char	*tmp;
	char	*dst;
	size_t	n;
	int		i;

	n = 64;
	while (k == 0)
	{
		i = 0;
		if (c == '\"')
			write(1, "dquote> ", 8);
		else
			write(1, "quote> ", 7);
		getline(&tmp, &n, stdin);
		while (tmp[i] && tmp[i] != c)
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

int	parse_expance(t_args *args, t_data *data, char c)
{
	if (ft_cmp(args->str, args->i, c) != 0)
	{
		if (parse_quote(args, c) == 1)
		{
			if (quote(args, data, c, 0) == 0)
				return (0);
		}
		else
		{
			if (start_expance(args, c, 0) == 0)
				return (0);
			if (quote(args, data, c, 0) == 0)
				return (0);
		}
	}
	return (1);
}
