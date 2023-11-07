/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:51:06 by ychair            #+#    #+#             */
/*   Updated: 2023/10/23 00:35:32 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static char	*create_string(char *src, int check, int i, char *tabsign)
{
	char	*dst;

	dst = NULL;
	dst = malloc(sizeof(char) * (i + 1 - check));
	if (!dst)
		return (NULL);
	dst[i - check] = '\0';
	while ((i - check > 0))
	{
		if (tabsign[0] && tabsign[1])
			dst[i - 3] = src[i - 2];
		else if (tabsign[0])
			dst[i - 2] = src[i - 1];
		else if (tabsign[1])
			dst[i - 2] = src[i - 2];
		i--;
	}
	return (dst);
}

static char	*final_string(char *src, char *tabsign)
{
	char	*tmp;

	if (tabsign[0])
	{
		if (tabsign[0] == '\"')
			tmp = ft_strjoin("\"", src);
		if (tabsign[0] == '\'')
			tmp = ft_strjoin("\'", src);
		free(src);
		src = truecpy(tmp);
		free(tmp);
	}
	if (tabsign[1])
	{
		if (tabsign[1] == '\"')
			tmp = ft_strjoin(src, "\"");
		if (tabsign[1] == '\'')
			tmp = ft_strjoin(src, "\'");
		free(src);
		src = truecpy(tmp);
		free(tmp);
	}
	return (src);
}

char	*chekgo(char *src, char *tabsign)
{
	int		i;
	char	*dst;
	int		check;

	check = 0;
	i = 0;
	if (tabsign[0])
		check++;
	if (tabsign[1])
		check++;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	if (i == 2 || i == 0)
		return (NULL);
	dst = create_string(src, check, i, tabsign);
	if (!dst)
		return (NULL);
	return (dst);
}

char	*chekg(char *src)
{
	int		i;
	char	*dst;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	if (i == 2 || i == 0)
		return (NULL);
	dst = malloc(sizeof(char) * i - 1);
	dst[i - 2] = '\0';
	while ((i - 2) > 0)
	{
		dst[i - 3] = src[i - 2];
		i--;
	}
	free(src);
	src = NULL;
	return (dst);
}

char	*nospace(char *src, char **env, int i)
{
	int		j;
	char	**dst;
	char	tabsign[2];

	tabsign[0] = '\0';
	tabsign[1] = '\0';
	dst = ft_split(src, ' ');
	if (!dst)
		return (NULL);
	while (dst[++i])
	{
		j = -1;
		while (dst[i][++j])
			;
		if (dst[i][0] == '\'' || dst[i][0] == '\"')
			tabsign[0] = dst[i][0];
		if (dst[i][j - 1] == '\'' || dst[i][j - 1] == '\"')
			tabsign[1] = dst[i][j - 1];
		dst[i] = set_dst(tabsign, dst, i, env);
	}
	src = new_src(dst, i, src);
	if (!src)
		return (NULL);
	return (final_string(src, tabsign));
}
