/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:36:57 by ychair            #+#    #+#             */
/*   Updated: 2023/10/04 00:42:28 by ychair           ###   ########.fr       */
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
char **executeAST(Node* node, int in_fd, int out_fd,char **env);
void    ASTrunner(Node *node,int nb);
void    printAST(Node* root);
#endif
