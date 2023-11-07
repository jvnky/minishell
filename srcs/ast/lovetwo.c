/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lovetwo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 01:23:47 by ychair            #+#    #+#             */
/*   Updated: 2023/10/26 01:48:21 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	opf(t_args *fd, t_node *node)
{
	int	file_fd;

	file_fd = 0;
	if (node->app == 1)
		file_fd = open(node->opf, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		file_fd = open(node->opf, O_WRONLY | O_CREAT, 0644);
	if (file_fd == -1)
		perror("No such file or directory");
	close(STDOUT_FILENO);
	fdgarbage(fd, file_fd);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
}

void	fdtout(t_args *fd)
{
	close(STDOUT_FILENO);
	fdgarbage(fd, fd->tout);
	dup2(fd->tout, STDOUT_FILENO);
	close(fd->tout);
}

void	sndchild(char *bins, t_args *fd, t_data *data)
{
	free(bins);
	free_all(fd, data);
	exit(0);
}

static void	argsquote(char **args, t_args *fd)
{
	int	i;

	i = -1;
	fdcloser(fd);
	while (args[++i])
	{
		if (args[i][0] == '\'' || args[i][0] == '\"')
			args[i] = chekg(args[i]);
	}
}

void	mychild(t_args *fd, t_data *data, char **env, char **args)
{
	char	*bins;

	argsquote(args, fd);
	if (access(args[0], F_OK) != 0)
	{
		bins = get_absolute_path(args, env, -1);
		if (!bins)
			bins = args[0];
		if (execve(bins, args, NULL) == -1)
		{
			free(bins);
			bins = NULL;
			free_all(fd, data);
			exit(3);
		}
	}
	else
	{
		if (execve(args[0], args, NULL) == -1)
		{
			free_all(fd, data);
			exit(5);
		}
	}
	sndchild(bins, fd, data);
}
