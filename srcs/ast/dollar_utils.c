/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:42:16 by ychair            #+#    #+#             */
/*   Updated: 2023/10/24 04:26:28 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

char	*change_dollar(char *src, int i, char *env)
{
	int		j;
	char	*dst;

	j = 0;
	while (j < i)
		j++;
	dst = malloc(sizeof(char) * (j + 1));
	if (!dst)
		return (NULL);
	dst[j] = '\0';
	while (--j >= 0)
		dst[j] = src[j];
	free(src);
	src = ft_strjoin(dst, env);
	free(dst);
	if (!src)
		return (NULL);
	free(env);
	env = NULL;
	return (src);
}

char	*set_dmp(char *src, int i)
{
	int		j;
	int		len;
	char	*dst;

	j = i;
	len = 0;
	while (src[++j])
		len++;
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	dst = ft_stricpy(dst, src, i + 1);
	return (dst);
}

char	*find_env(char *src, int i, char **env)
{
	char	*dmp;
	char	*envu;

	envu = NULL;
	dmp = set_dmp(src, i);
	if (!dmp)
		return (NULL);
	if (env_value(env, dmp) != -1)
		envu = cd_option_utils(env, envu, dmp);
	else if (dmp[0] == '?' && !dmp[1])
		envu = ft_itoa(g_ret_number);
	else
	{
		envu = malloc(sizeof(char) * 1);
		envu[0] = '\0';
	}
	src = change_dollar(src, i, envu);
	free(dmp);
	return (src);
}

char	*new_src(char **dst, int i, char *srcs)
{
	char	*src;
	int		j;

	if (srcs)
	{
		free(srcs);
		srcs = NULL;
	}
	j = -1;
	src = NULL;
	while (++j < i)
	{
		if (!src)
			src = truecpy(dst[j]);
		else
		{
			srcs = ft_strjoin(src, dst[j]);
			free(src);
			src = truecpy(srcs);
			free(srcs);
		}
	}
	free_array(dst);
	return (src);
}

char	*envdol(char *src, char **env)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	dst = ft_split(src, ' ');
	if (!dst)
		return (NULL);
	while (dst[i])
	{
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
	return (src);
}
