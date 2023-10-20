/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:28:20 by cofoundo          #+#    #+#             */
/*   Updated: 2023/10/20 01:10:16 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <curses.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "env.h"
# include "parser.h"
# include "structure.h"
# include "structast.h"
# include "ast.h"

extern int		g_ret_number;

char	*ft_atoa(char *str);
char	*ft_itoa(int n);

int		init_struct(t_args *args, t_data *data);
int		init_data(t_data *data);
int		init_args(t_args *args);
int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		main(int ac, char **av, char **enve);

void	free_all(t_args *args, t_data *data);
void	freeast(t_node *root);
void	free_data(t_data *data);
void	free_args(t_args *args);
void	setup_term(void);


#endif
