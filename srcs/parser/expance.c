/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 21:33:41 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/24 02:07:31 by cofoundo         ###   ########.fr       */
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

int	parse_expance(t_args *args, t_data *data, char c)
{
	if (ft_cmp(args->str, args->i, c) != 0)
	{
		if (parse_quote(args, c) == 1)
		{
			if (quote(args, data, c, 2) == 0)
				return (0);
		}
		else
			return (0);
	}
	return (1);
}
