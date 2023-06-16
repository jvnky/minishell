/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:36:57 by ychair            #+#    #+#             */
/*   Updated: 2023/06/16 17:27:03 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TEST_H
# define TEST_H

#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* command;
    char** arguments;
    int numArguments;
    char* inputFile;
    char* outputFile;
    struct Node* left;
    struct Node* right;
} Node;

Node* buildast(char ***commands, int lent);
void executeAST(Node* node, int in_fd, int out_fd);
//  void executeAST(Node* node);
#endif
