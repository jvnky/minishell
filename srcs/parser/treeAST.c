/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeAST.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:37:03 by ychair            #+#    #+#             */
/*   Updated: 2023/03/24 02:40:21 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

ast_node* createNode(char *value) {
    ast_node *newNode = (ast_node*)malloc(sizeof(ast_node));
	//newNode->cmd = (ast_comd*)malloc(sizeof(ast_comd));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
	newNode->cmd = NULL;
    return newNode;
}


ast_node* buildAST(char ***data, int numLines,ast_node *root) {

	// ast_node *root = NULL;
    ast_node *currentNode = NULL;
    ast_node *lastPipeNode = NULL;
	ast_node *firstPipeNode = NULL;
    int i, j,k ;

    i = 0;
    while (i < numLines) {
        j = 0;
		k = 0;

        while (data[i][j])
		{
            if (numLines == 1)
            {
                ast_node *newNode = createNode(data[i][j]);
				newNode->cmd->redirect_type = data[i][j];
				root = newNode;
                break;
            }
            if (data[i][j] == NULL)
                break;
           if (*data[i][j] == '|' || *data[i][j] == '<' || *data[i][j] == '>'){
                ast_node *newNode = createNode(data[i][j]);
				if (*data[i][j] == '|')
					newNode->type = AST_PIPE;
				if (*data[i][j] == '>')
					newNode->type = AST_REDOUT;
				if (*data[i][j] == '<')
					newNode->type = AST_REDIN;
				if(lastPipeNode != NULL)
                    lastPipeNode = lastPipeNode->right;
				if (i == 1)
					{
						firstPipeNode = newNode;
						root = firstPipeNode;
					}
                lastPipeNode = newNode;
				if (lastPipeNode != NULL && firstPipeNode != NULL)
				{
					firstPipeNode->right = lastPipeNode;
					firstPipeNode = lastPipeNode;
		   		}
                if(currentNode != NULL)
                {
                    lastPipeNode->left = currentNode;
                }
            }
            else {
                if ((i == 0 && j > 0)||(i > 0 && j > 1))
				{
					currentNode->cmd = (ast_comd*)malloc(sizeof(ast_comd));
					currentNode->cmd->args[k] = data[i][j];
					k++;
				}
				else
				{
					ast_node *newNode = createNode(data[i][j]);
					newNode->type = AST_ARG;
					currentNode = newNode;
				}
            }
            j++;
        }
			//currentNode->cmd->args[k] = "\0";
			// last node to put at the end of ast
            if (currentNode != NULL && lastPipeNode != NULL && i == numLines-1)
                lastPipeNode->right = currentNode;
        i++;
    }
    return root;
}
