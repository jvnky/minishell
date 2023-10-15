/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:36:57 by ychair            #+#    #+#             */
/*   Updated: 2023/10/15 05:23:00 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTAST_H
# define STRUCTAST_H

# include "minishell.h"

typedef struct Node
{
	struct Node	*right;
	struct Node	*left;
	char		**arguments;
	char		*command;
	char		*inputFile;
	char		*outputFile;
	int			app;
	int			numArguments;
	int			quote;
}	Node;

Node	*astheredocs(char ***commands, int lent, int i, int j);
Node	*buildast(char ***commands, int lent);

char	**executeAST(Node *node, char **env, t_args *args, t_data *data);
char	*truecpy(char *src);
char	*chekg(char *src);

void	ASTrunner(Node *node, int nb);
void	printAST(Node *root);
void	restore_prompt(int sig);
void	run_signals(int sig);
#endif
