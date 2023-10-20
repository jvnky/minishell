/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:42:16 by ychair            #+#    #+#             */
/*   Updated: 2023/10/20 05:09:32 by ychair           ###   ########.fr       */
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
	return (src);
}

char	*set_dmp(char *src, int i)
{
	int		j;
	int		len;
	char	*dst;
	// printf("II = %d SRC %s\n",i,src);
	j = i;
	len = 0;
	while (src[++j])
		len++;
	// printf("len %d\n",len);
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
	// int k =0;
	// while(env[k])
		// printf("ENV = %s\n",env[k++]);
	envu = NULL;
	// printf("I = %d src1 = %s\n",i,src);
	dmp = set_dmp(src, i);
	// printf("dmp = %s \n",dmp);
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
	// printf("ENVU = %s\n",envu);
	src = change_dollar(src, i, envu);
	free(dmp);
	if (envu)
		free(envu);
	// printf("SRC = %s\n",src);
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
	// printf("src = %s\n",src);
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
			// printf("J = %d\n",j);
			// printf("J =  %d 1DST = %s\n",j,dst[i]);
			dst[i] = find_env(dst[i], j, env);
			// printf("DST = %s\n",dst[i]);
			i++;
		}
		else
			i++;
	}
	// printf("DST = %s"\n,dst[i]);
	src = new_src(dst, i,src);
	if (!src)
		return (NULL);
	return (src);
}
