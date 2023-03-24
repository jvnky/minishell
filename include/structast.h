/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:36:57 by ychair            #+#    #+#             */
/*   Updated: 2023/03/22 01:42:14 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TEST_H
# define TEST_H

#include <stdlib.h>
#include <string.h>
// Structure for a shell command
#define MAX_ARGS 64
#define MAX_COMMANDS 16


typedef enum type{
	 AST_ARG ,
	 AST_PIPE ,
	 AST_REDIN ,
	 AST_REDOUT ,
}tag;

typedef struct command {
    char *args[MAX_ARGS];//The arguments for the command
    int fd_in; // fd input
    int fd_out; // fd output
	char *redirect_type; // < > >> <<
    char *redirect_file; // file fds
}ast_comd;

// Structure for the AST tree node
typedef struct ast_node {
	char * value;
	tag type;
    struct command *cmd;
    struct ast_node *left;
    struct ast_node *right;
}ast_node;



ast_node* buildAST(char ***data, int numLines,ast_node *root);
void	runrun(ast_node *root,int input_fd, int output_fd);
#endif
