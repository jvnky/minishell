/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:26:51 by cofoundo          #+#    #+#             */
/*   Updated: 2021/10/07 17:57:04 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exit(int i, char *str)
{
	write(2, str, ft_strlen(str));
	exit(i);
}

int	child(int *pipe_fd, int *file_fd, char **av, char **path_list)
{
	char	**command;
	char	*path_command;

	close(pipe_fd[1]);
	dup2(file_fd[1], 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	command = ft_split(av[3], ' ');
	if (command == NULL)
		ft_exit(-1, "Error with malloc\n");
	path_command = get_path(command[0], path_list);
	if (!path_command)
	{
		if (!command[0])
			ft_exit(-1, "Permission denied\n");
		free_split(command);
		ft_exit(-1, "Error with malloc\n");
	}
	if (execve(path_command, command, NULL) == -1)
		ft_exit(-1, "Command not found\n");
	return (0);
}

int	parent(int *pipe_fd, int *file_fd, char **av, char **path_list)
{
	char	**command;
	char	*path_command;

	close(pipe_fd[0]);
	dup2(file_fd[0], 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	command = ft_split(av[2], ' ');
	if (command == NULL)
		ft_exit(-1, "Error with malloc\n");
	path_command = get_path(command[0], path_list);
	if (!path_command)
	{
		if (!command[0])
			ft_exit(-1, "Permission denied\n");
		free_split(command);
		ft_exit(-1, "Error with malloc\n");
	}
	if (execve(path_command, command, NULL) == -1)
		ft_exit(-1, "Command not found\n");
	return (0);
}
