/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeAST.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:37:03 by ychair            #+#    #+#             */
/*   Updated: 2023/10/19 01:02:03 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

t_node	*createnode(char *command)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	// if(node->command)
	// 	free(node->command);
	node->command = NULL;
	node->command = truecpy(command);
	node->numarguments = 0;
	node->arguments = NULL;
	node->ipf = NULL;
	node->opf = NULL;
	node->left = NULL;
	node->right = NULL;
	node->app = 0;
	return (node);
}

int	setarguments(t_node *node, char **arguments)
{
	int	numarguments;
	int	i;

	i = 0;
	numarguments = 0;
	while (arguments[numarguments] != NULL)
		numarguments++;
	// printf("NUM =%d\n",numarguments);
	if (numarguments > 0)
	{
		// printf("NUM =%d\n",numarguments);
		node->arguments = (char **)malloc((numarguments + 1) * sizeof(char *));
		while (i < numarguments)
		{
			node->arguments[i] = truecpy(arguments[i]);
			i++;
		}
		node->arguments[numarguments] = NULL;
		node->numarguments = numarguments;
	}
	return (numarguments);
}

int	checkop(char *command)
{
	if (ft_strcmp(command, ">") != 0 && ft_strcmp(command, "<") != 0
		&& ft_strcmp(command, ">>") != 0 && ft_strcmp(command, "<<") != 0)
		return (1);
	else
		return (0);
}

int	checkopc(char command)
{
	if (command == '>' || command == '<')
		return (1);
	else
		return (0);
}

t_node	*buildast(char ***commands, int lent)
{
	t_node	*root;
	t_node	*current;
	t_node	*prev;
	t_node	*newnode;
	t_node	*operatornode;
	int		i;
	int		j;
	char	*command;/*trop de variable*/

	root = NULL;
	current = NULL;
	prev = NULL;
	i = 0;
	while (i < lent)
	{
		j = 0;
		while (commands[i] && commands[i][j])
		{
			command = truecpy(commands[i][j]);
			if (ft_strcmp(command, "|") == 0)
			{
				operatornode = createnode(command);
				if (!operatornode)
					return (NULL);
				free(command);
				if (root == NULL)
				{
					operatornode->left = current;
					prev = operatornode;
					root = operatornode;
				}
				else
				{
					operatornode->left = current;
					prev->right = operatornode;
				}
				prev = operatornode;
			}
			else
			{
				newnode = createnode(command);
				free(command);
				if (checkop(newnode->command))
				{
					if ((i == 0) || (i > 0 && commands[i][j - 1] != NULL
						&& checkopc(commands[i][j - 1][0]) == 0))
					{
						if ((i == 0 && j == 0) || i > 0)
								current = newnode;
					}
					if (i == lent - 1 && i > 0 && prev)
						prev->right = current;
					if (commands[i][j + 1] && (commands[i][j + 1][0] == '-'
						|| checkop(commands[i][j + 1])))
					{
						j += setarguments(current, &(commands[i][j + 1]));
						if (i > 0)
							j++;
					}
					if ((commands[i + 1] && commands[i + 1][0][0] == '>')
							|| (commands[i][j + 1]
							&& commands[i][j + 1][0] == '>'))
					{
						current->opf = truecpy(commands[i + 1][1]);
						if (commands[i + 1][0][1] == '>')
							current->app = 1;
					}
					if ((commands[i + 1] && commands[i + 1][0][0] == '<')
							|| (commands[i][j + 1]
							&& commands[i][j + 1][0] == '<'))
							current->ipf = truecpy(commands[i + 1][1]);
					if (commands[i + 1] && commands[i + 1][0][0] == '<'
							&& commands[i + 1][0][1] == '<')
					{
						current->app = 2;
						current = astheredocs(commands, lent, i, j);
						if (!root && current)
							root = current;
						if (prev)
							prev->right = current;
						return (root);
					}
				}
			}
			j++;
		}
		i++;
	}
	if (!root && current)
		root = current;
	return (root);
}


t_node *astheredocs(char*** commands, int lent,int i,int j) {
    t_node* root = NULL;
    t_node* current = NULL;
    t_node* prev = NULL;


    // int i = 0;
    while (i < lent) {
        // int j = 0;
        while (commands[i][j]) {
            char* command = truecpy(commands[i][j]);
            // printf("i == %d .  %s\n",i,commands[i][j]);
            if (ft_strcmp(command, "|") == 0) {
                t_node* operatorNode = createnode(command);

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
                t_node* newNode = createnode(command);
                //  printf("i == %d . j == %d ,  %s\n",i,j,commands[i][j]);
                if(checkop(newNode->command)){
                    if((i == 0) || (i > 0 && commands[i][j - 1] != NULL &&
                         checkopc(commands[i][j-1][0]) == 0))
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
                                setarguments(current, &(commands[i][j + 1]));
                                j++;
                            }
                    }
                    if(commands[i+1] != NULL && commands[i+1][0][0] == '>')
                    {
                        current->opf = truecpy(commands[i+1][1]);
                    }
                    if(commands[i+1] != NULL && commands[i+1][0][0] == '>' && commands[i+1][0][1] == '>')
                    {
                        current->app = 1;
                    }
                    if(commands[i+1] != NULL && commands[i+1][0][0] == '<')
                    {
                        current->ipf = truecpy(commands[i+1][1]);
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
