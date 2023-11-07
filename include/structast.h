/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:36:57 by ychair            #+#    #+#             */
/*   Updated: 2023/10/24 04:32:29 by cofoundo         ###   ########.fr       */
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

typedef struct s_num
{
	int		i;
	int		j;
	int		lent;
	int		checkr;
	char	*command;
	t_node	*operatornode;
	t_node	*root;
	t_node	*current;
	t_node	*prev;
	t_node	*newnode;

}	t_num;

t_node	*astheredocs(char ***commands, int lent, int i, int j);
t_node	*buildast(char ***commands, t_num *num);

char	**executeast(t_node *node, char **env, t_args *args, t_data *data);
char	*truecpy(char *src);
char	*chekg(char *src);

void	printAST(t_node *root);
void	restore_prompt(int sig);
void	run_signals(int sig);
#endif
