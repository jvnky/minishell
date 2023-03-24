/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:02:58 by cofoundo          #+#    #+#             */
/*   Updated: 2021/10/08 13:43:53 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	malloc_error(void)
{
	write(2, "Error malloc\n", ft_strlen("Error malloc\n"));
	return (-1);
}

int	argument(void)
{
	write(2, "Wrong number of argument\n",
		ft_strlen("Wrong number of argument\n"));
	return (-1);
}

void	error_read(char *str)
{
	if (errno == 0)
		error();
	else
	{
		write(2, "permision denied on : ",
			ft_strlen("permision denied on : "));
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
}

void	error(void)
{
	char	*str;

	str = strerror(errno);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	error_file(char *str)
{
	if (errno == 0)
		error();
	else
	{
		write(2, "No such file or directory: ",
			ft_strlen("No such file or directory: "));
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	exit(errno);
}
