/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeAST.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofoundo <cofoundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:37:03 by ychair            #+#    #+#             */
/*   Updated: 2023/10/15 02:42:03 by cofoundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"


Node* createNode(char* command) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->command = truecpy(command);
    node->numArguments = 0;
    node->arguments = NULL;
    node->inputFile = NULL;
    node->outputFile = NULL;
    node->left = NULL;
    node->right = NULL;
    node->app = 0; // 1 >> / 2 <<
    return node;
}

int setArguments(Node* node, char** arguments) {
    
    int numArguments = 0;
    while (arguments[numArguments] != NULL) {
        numArguments++;
    }
    // printf("ARGU = %d\n",numArguments);
    if (numArguments > 0) {
        node->arguments = (char**)malloc((numArguments + 1) * sizeof(char*));
        for (int i = 0; i < numArguments; i++) {
            node->arguments[i] = truecpy(arguments[i]);
        }
        node->arguments[numArguments] = NULL;
        node->numArguments = numArguments;
    }
    return (numArguments);
}

int checkop(char* command)
{
    if (strcmp(command, ">") != 0 && strcmp(command, "<") != 0 &&
                strcmp(command, ">>") != 0 && strcmp(command, "<<") != 0)
        return(1);
    else
        return(0);
}

int checkopC(char command)
{
    if (command == '>' || command == '<')
        return(1);
    else
        return(0);
}


// Node* astheredocs(char*** commands, int lent,int i,int j);

Node* buildast(char*** commands, int lent) {
    Node* root = NULL;
    Node* current = NULL;
    Node* prev = NULL;
    int i;
    int j;
    char *command;

    i = 0;
    while (i < lent) {
        j = 0;
        while (commands[i][j]) {
            command = truecpy(commands[i][j]);
            // printf("i == %d .  %s\n",i,commands[i][j]);
            if (strcmp(command, "|") == 0) {
                Node* operatorNode = createNode(command);
                free(command);
                if (root == NULL) {
                    operatorNode->left = current;
                    prev = operatorNode;
                    root = operatorNode;
                } else {
                       operatorNode->left = current;
                       prev->right = operatorNode;
                }
                prev = operatorNode;
            } else{
                Node* newNode = createNode(command);
                free(command);
                //  printf("i == %d . j == %d ,  %s\n",i,j,commands[i][j]);
                if(checkop(newNode->command)){
                    if((i == 0) || (i > 0 && commands[i][j - 1] != NULL &&
                         checkopC(commands[i][j-1][0]) == 0))
                    {
                            if((i == 0 && j == 0) || i > 0)
                                current = newNode;
                    }
                //    printf("j =%d    = %s  = %s  \n",j,commands[i][j],commands[i][j+1]);
                    if(i == lent -1  && i > 0 && prev != NULL)
                    {
                        prev->right = current;
                    }
                    // if (current->command[0] == '\"' || current->command[0] == '\'')
                    //     current->command = checkg(current->command);
                     if(commands[i][j+1] != NULL && (commands[i][j+1][0] == '-' || checkop(commands[i][j+1])))
                    {
                                j=+setArguments(current, &(commands[i][j + 1]));
                                if(i > 0)
                                    j++;
                    }
                    if((commands[i+1] != NULL && commands[i+1][0][0] == '>') || (commands[i][j + 1] != NULL && commands[i][j + 1][0] == '>'))
                    {
						current->outputFile = truecpy(commands[i+1][1]);
						if(commands[i+1][0][1] == '>')
							current->app = 1;
                    }
                    if((commands[i+1] != NULL && commands[i+1][0][0] == '<') || (commands[i][j + 1] != NULL && commands[i][j + 1][0] == '<'))
                    {
                        current->inputFile = truecpy(commands[i+1][1]);
                    }
                    if(commands[i+1] != NULL && commands[i+1][0][0] == '<' && commands[i+1][0][1] == '<')
                    {
                        current->app = 2;
                        current = astheredocs(commands,lent,i,j);
                         if (root == NULL && current != NULL)
                             root = current;
                        if(prev != NULL)
                            prev->right = current;
                        return(root);
                    }
                }
            }
            j++;
        }
        i++;
    }
    if (root == NULL && current != NULL)
             root = current;
    return root;
}

Node* astheredocs(char*** commands, int lent,int i,int j) {
    Node* root = NULL;
    Node* current = NULL;
    Node* prev = NULL;


    // int i = 0;
    while (i < lent) {
        // int j = 0;
        while (commands[i][j]) {
            char* command = truecpy(commands[i][j]);
            // printf("i == %d .  %s\n",i,commands[i][j]);
            if (strcmp(command, "|") == 0) {
                Node* operatorNode = createNode(command);

                if (root == NULL) {
                    operatorNode->left = current;
                    prev = operatorNode;
                    root = operatorNode;
                } else {
                       operatorNode->left = current;
                       prev->right = operatorNode;
                }
                prev = operatorNode;
            } else{
                Node* newNode = createNode(command);
                //  printf("i == %d . j == %d ,  %s\n",i,j,commands[i][j]);
                if(checkop(newNode->command)){
                    if((i == 0) || (i > 0 && commands[i][j - 1] != NULL &&
                         checkopC(commands[i][j-1][0]) == 0))
                    {
                            if((i == 0 && j == 0) || i > 0)
                                current = newNode;
                    }
                //    printf("j =%d    = %s  = %s  ",j,commands[i][j],commands[i][j+1]);
                    if(i == lent -1  && i > 0 && prev != NULL)
                    {
                        prev->right = current;
                    }
                    //REFAIRE ALGO PLUS DE ""
                    if(commands[i][j+1] != NULL && (commands[i][j+1][0] == '-' || checkop(commands[i][j+1])))
                    {
                        //CHECK le WHILE
                            while(commands[i][j+1] != NULL &&checkop(commands[i][j+1]))
                            {
                                setArguments(current, &(commands[i][j + 1]));
                                j++;
                            }
                    }
                    if(commands[i+1] != NULL && commands[i+1][0][0] == '>')
                    {
                        current->outputFile = truecpy(commands[i+1][1]);
                    }
                    if(commands[i+1] != NULL && commands[i+1][0][0] == '>' && commands[i+1][0][1] == '>')
                    {
                        current->app = 1;
                    }
                    if(commands[i+1] != NULL && commands[i+1][0][0] == '<')
                    {
                        current->inputFile = truecpy(commands[i+1][1]);
                    }
                    if(commands[i+1] != NULL && commands[i+1][0][0] == '<' && commands[i+1][0][1] == '<')
                    {
                        current->app = 2;
                        
                    }
                }
            }
            j++;
        }
        i++;
        j= 0;
    }

    if (root == NULL && current != NULL)
             root = current;
    return root;
}