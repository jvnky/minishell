/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolut_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:47:38 by ychair            #+#    #+#             */
/*   Updated: 2023/10/20 05:55:22 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

char	*truecpy(char *src)
{
	int		i;
	char	*dst;

	i = ft_strlen(src);
	dst = malloc(sizeof(char) * i + 1);
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	// free(src);
	// src = NULL;
	return (dst);
}

int	ft_strlcpy(char *dst, char *src)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (src[count] != '\0')
		++count;
	while (src[i] != '\0' && i != count - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (count > 0)
		dst[i] = '\0';
	return (count);
}

int	checkbuilt(t_node *node)
{
	if (strcmp(node->command, "echo") == 0)
		return (1);
	if (strcmp(node->command, "echo -n") == 0)
		return (8);
	if (strcmp(node->command, "cd") == 0)
		return (2);
	if (strcmp(node->command, "pwd") == 0)
		return (3);
	if (strcmp(node->command, "export") == 0)
		return (4);
	if (strcmp(node->command, "unset") == 0)
		return (5);
	if (strcmp(node->command, "env") == 0)
		return (6);
	if (strcmp(node->command, "exit") == 0)
		return (7);
	return (0);
}
