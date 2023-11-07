/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 23:53:26 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/23 00:17:04 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

char	*set_dst(char *tabsign, char **dst, int i, char **env)
{
	char	*tmp;
	int		j;

	if (tabsign[0] || tabsign[1])
	{
		tmp = chekgo(dst[i], tabsign);
		free(dst[i]);
		dst[i] = tmp;
	}
	j = -1;
	while (dst[i][++j] && dst[i][j] != '$')
		;
	if (dst[i][j] && dst[i][j] == '$')
		dst[i] = find_env(dst[i], j, env);
	return (dst[i]);
}

int	ft_strcmpa(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
