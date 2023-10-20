/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:36:57 by ychair            #+#    #+#             */
/*   Updated: 2023/10/18 00:54:47 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTAST_H
# define STRUCTAST_H

# include "minishell.h"

typedef struct s_node
{
	struct s_node	*right;
	struct s_node	*left;
	char			**arguments;
	char			*command;
	char			*ipf;
	char			*opf;
	int				app;
	int				numarguments;
	int				quote;
}	t_node;

t_node	*astheredocs(char ***commands, int lent, int i, int j);
t_node	*buildast(char ***commands, int lent);

char	**executeast(t_node *node, char **env, t_args *args, t_data *data);
char	*truecpy(char *src);
char	*chekg(char *src);

void	printAST(t_node *root);
void	restore_prompt(int sig);
void	run_signals(int sig);
#endif
