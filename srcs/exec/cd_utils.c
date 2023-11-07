/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 23:49:24 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/26 02:09:17 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cd_option(char *str)
{
	if (ft_strcompr(str, "..") == 1)
		return (1);
	else if (ft_strcompr(str, "/") == 1)
		return (2);
	else if (ft_strcompr(str, "-") == 1)
		return (3);
	else if (ft_strcompr(str, "~") == 1 || !str)
		return (4);
	else if (ft_strcompr(str, "~root") == 1)
		return (5);
	return (0);
}

void	freeone(char *line, int fd)
{
	free(line);
	line = NULL;
	close(fd);
}

char	**executecommand(t_node *node, t_args *fd, t_data *data, char **env)
{
	int		checkbuiltin;
	char	**args;

	args = argumentsexec(node);
	if (node->ipf && node->app == 2)
		ft_heredocs(node, env, 0);
	if (node->ipf)
		ipf(node, fd);
	else if (fd->tin != STDIN_FILENO)
		fdtin(fd);
	if (node->opf != NULL)
		opf(fd, node);
	else if (fd->tout != STDOUT_FILENO)
		fdtout(fd);
	checkbuiltin = checkbuilt(node);
	if (checkbuiltin)
		env = execbuiltin(node, env, fd, data);
	else if (family(fd, data, env, args) != NULL)
		return (writeme(node, args, env));
	free(args);
	return (env);
}
