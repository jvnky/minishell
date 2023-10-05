/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:28:20 by cofoundo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/28 23:56:24 by cofoundo         ###   ########.fr       */
=======
/*   Updated: 2023/06/22 01:44:22 by cofoundo         ###   ########.fr       */
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include "parser.h"
# include "structure.h"
# include "structast.h"
# include "env.h"
<<<<<<< HEAD
=======
//# include "pipex.h"
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742

# define MINUS_STR "----------------------------------------------------------------------------------------------------"
# define TEST "\033[36;01m(%s:%d:0) \033[31;01m%s\033[0m %.*s>\033[35;01m%d\033[0m\n", __FILE__, __LINE__, __FUNCTION__, (int)(70 - (strlen(__FUNCTION__) + strlen(__FILE__) + 3)), MINUS_STR, __LINE__

<<<<<<< HEAD
int		init_struct(t_args *args, t_data *data, t_history *history);
int		init_data(t_data *data);
int		init_args(t_args *args);
int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		main(int ac, char **av, char **enve);
void	free_all(t_args *args, t_data *data);
void	free_data(t_data *data);
void	free_args(t_args *args);
void	free_history(t_history *history);
=======
int init_struct(t_args *args, t_data *data, t_history *history);
int init_data(t_data *data);
int init_args(t_args *args);
int ft_strlen(char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int main();
void    free_all(t_args *args, t_data *data);
void    free_data(t_data *data);
void    free_args(t_args *args);
void    free_history(t_history *history);
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
#endif
