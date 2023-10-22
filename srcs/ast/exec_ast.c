/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:51:06 by ychair            #+#    #+#             */
/*   Updated: 2023/10/21 22:46:03 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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
	return (dst);
}

char	*chekgo(char *src,char *tabsign)
{
	int		i;
	char	*dst;
	int 	check;

	check = 0;
	i = 0;
	if(tabsign[0])
		check++;
	if(tabsign[1])
		check++;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	if (i == 2 || i == 0)
		return (NULL);
	dst = malloc(sizeof(char) * (i + 1 - check));
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

char	*nospace(char *src, char **env)
{
	int		i;
	int		j;
	char	**dst;
	char	*tmp;
	char	tabsign[2];

	tabsign[0] = '\0';
	tabsign[1] = '\0';
	i = 0;
	dst = ft_split(src, ' ');
	if (!dst)
		return (NULL);
	while (dst[i])
	{
		j = -1;
		while (dst[i][++j])
			;
		if (dst[i][0] == '\'' || dst[i][0] == '\"')
			tabsign[0] = dst[i][0];
		printf("ntm : %d\n", j);
		if (dst[i][j - 1] == '\'' || dst[i][j - 1] == '\"')
		{
			puts("NTM BATARD");
			tabsign[1] = dst[i][j - 1];
			printf("ntm : %c\n", tabsign[1]);
		}
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
		{
			dst[i] = find_env(dst[i], j, env);
			i++;
		}
		else
			i++;
	}
	src = new_src(dst, i, src);
	if (!src)
		return (NULL);
	if(tabsign[0])
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
