/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:36:57 by ychair            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/04 00:42:28 by ychair           ###   ########.fr       */
=======
/*   Updated: 2023/08/05 00:38:03 by ychair           ###   ########.fr       */
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
/*                                                                            */
/* ************************************************************************** */


#ifndef TEST_H
# define TEST_H

#include <stdlib.h>
#include <string.h>
#include "minishell.h"

typedef struct Node {
    char* command;
    char** arguments;
    int numArguments;
    char* inputFile;
    char* outputFile;
    struct Node* left;
    struct Node* right;
    int  app; // 1 >> / 2 <<
} Node;

Node* buildast(char ***commands, int lent);
<<<<<<< HEAD
char **executeAST(Node* node, int in_fd, int out_fd,char **env);
void    ASTrunner(Node *node,int nb);
void    printAST(Node* root);
=======
void executeAST(Node* node, int in_fd, int out_fd);
void    ASTrunner(Node *node,int nb);

>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
#endif
