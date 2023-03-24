/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:31:58 by cofoundo          #+#    #+#             */
/*   Updated: 2021/10/07 17:06:17 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_access_one(char **av)
{
	if (access(av[1], F_OK) == -1)
	{
		error_file(av[1]);
		exit(errno);
	}
	if (access(av[1], R_OK) == -1)
	{
		error_read(av[1]);
		exit(errno);
	}
}

static void	ft_acces_two(char **av)
{
	if (access(av[4], W_OK) == -1)
	{
		error_read(av[4]);
		exit (errno);
	}
}

static void	pipe_error(int pipe_id)
{
	if (pipe_id == -1)
	{
		error();
		exit(errno);
	}
}

static void	ft_exit(void)
{
	error();
	exit(errno);
}

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	int		file_fd[2];
	int		pipe_id;
	char	**path_list;

	if (ac != 5)
		return (argument());
	file_fd[1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_access_one(av);
	file_fd[0] = open(av[1], O_RDONLY);
	if (file_fd[0] == -1)
		error_file(av[1]);
	ft_acces_two(av);
	if (file_fd[1] == -1 || pipe(pipe_fd) == -1)
		ft_exit();
	pipe_id = fork();
	pipe_error(pipe_id);
	path_list = all_path(env);
	if (!path_list)
		return (malloc_error());
	if (pipe_id == 0)
		child(pipe_fd, file_fd, av, path_list);
	else
		return (parent(pipe_fd, file_fd, av, path_list));
	return (0);
}
