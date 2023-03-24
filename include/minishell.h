/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:28:20 by cofoundo          #+#    #+#             */
/*   Updated: 2023/02/26 00:39:56 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include "parser.h"
# include "structure.h"
# include "structast.h"
//# include "pipex.h"

# define MINUS_STR "----------------------------------------------------------------------------------------------------"
# define TEST "\033[36;01m(%s:%d:0) \033[31;01m%s\033[0m %.*s>\033[35;01m%d\033[0m\n", __FILE__, __LINE__, __FUNCTION__, (int)(70 - (strlen(__FUNCTION__) + strlen(__FILE__) + 3)), MINUS_STR, __LINE__

int init_struct(t_args *args, t_data *data);
int init_data(t_data *data);
int init_args(t_args *args);
int ft_strlen(char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int main();
void    free_all(t_args *args, t_data *data);
void    free_data(t_data *data);
void    free_args(t_args *args);
#endif
