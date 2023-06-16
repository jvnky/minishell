/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeAST.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:37:03 by ychair            #+#    #+#             */
/*   Updated: 2023/06/16 17:39:33 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


Node* createNode(char* command) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->command = strdup(command);
    node->numArguments = 0;
    node->arguments = NULL;
    node->inputFile = NULL;
    node->outputFile = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void setArguments(Node* node, char** arguments) {
    int numArguments = 0;
    while (arguments[numArguments] != NULL) {
        numArguments++;
    }

    if (numArguments > 0) {
        node->arguments = (char**)malloc((numArguments + 1) * sizeof(char*));
        for (int i = 0; i < numArguments; i++) {
            node->arguments[i] = strdup(arguments[i]);
        }
        node->arguments[numArguments] = NULL;
        node->numArguments = numArguments;
    }
}

Node* buildast(char*** commands, int lent) {
    Node* root = NULL;
    Node* current = NULL;
    Node* previous = NULL;

    int i = 0;
    while (i < lent) {
        int j = 0;
        while (commands[i][j]) {
            char* command = strdup(commands[i][j]);

            if (root == NULL) {
                root = createNode(command);
                current = root;
            } else {
                Node* newNode = createNode(command);

                if (strcmp(command, "|") == 0 || strcmp(command, ">") == 0 || strcmp(command, "<") == 0) {
                    current->right = newNode;
                    previous = current;
                    current = newNode;
                } else {
                    current->left = newNode;
                    previous = current;
                    current = newNode;
                }
                while (previous != NULL && previous->right != NULL) {
                    previous = previous->right;
                    current = previous;
                }
            }

            if (strcmp(command, "|") != 0 && strcmp(command, ">") != 0 && strcmp(command, "<") != 0 &&
                commands[i][j + 1] != NULL && strcmp(command, ">>") != 0 && strcmp(command, "<<") != 0) {
                setArguments(current, &(commands[i][j + 1]));
                break;  // Skip to next row
            } else if (strcmp(command, "<<") == 0 && commands[i][j + 1] != NULL) {
                current->inputFile = strdup(commands[i][j + 1]);
                j++;
            }  else if (strcmp(command, ">>") == 0 && commands[i][j + 1] != NULL) {
                current->outputFile = strdup(commands[i][j + 1]);
                j++;
            }  else if (strcmp(command, ">") == 0 && commands[i][j + 1] != NULL) {
                current->outputFile = strdup(commands[i][j + 1]);
                 j++;
            } else if (strcmp(command, "<") == 0 && commands[i][j + 1] != NULL) {
                current->inputFile = strdup(commands[i][j + 1]);
                 j++;
            } 
            j++;
        }
        i++;
    }

    return root;
}