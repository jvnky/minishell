/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolut_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:47:38 by ychair            #+#    #+#             */
/*   Updated: 2023/10/22 22:44:39 by cofoundo         ###   ########.fr       */
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
	if (ft_strcmpa(node->command, "echo") == 0)
		return (1);
	if (ft_strcmpa(node->command, "echo -n") == 0)
		return (8);
	if (ft_strcmpa(node->command, "cd") == 0)
		return (2);
	if (ft_strcmpa(node->command, "pwd") == 0)
		return (3);
	if (ft_strcmpa(node->command, "export") == 0)
		return (4);
	if (ft_strcmpa(node->command, "unset") == 0)
		return (5);
	if (ft_strcmpa(node->command, "env") == 0)
		return (6);
	if (ft_strcmpa(node->command, "exit") == 0)
		return (7);
	return (0);
}
