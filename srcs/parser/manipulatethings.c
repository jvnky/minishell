/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulatethings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:14:34 by ychair            #+#    #+#             */
/*   Updated: 2023/03/24 02:45:48 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"




// void execute_pipe(ast_node* node, int input_fd, int output_fd) {
//     int pipe_fds[2];

//     // Create a pipe
//     if (pipe(pipe_fds) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     // Fork a child process to execute the left subtree of the pipe node
//     pid_t left_pid = fork();
//     if (left_pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (left_pid == 0) {
//         // Child process
//         close(pipe_fds[0]); // Close the read end of the pipe
//         runrun(node->left, input_fd, pipe_fds[1]);
//         exit(EXIT_SUCCESS);
//     }

//     // Fork another child process to execute the right subtree of the pipe node
//     pid_t right_pid = fork();
//     if (right_pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (right_pid == 0) {
//         // Child process
//         close(pipe_fds[1]); // Close the write end of the pipe
//         runrun(node->right, pipe_fds[0], output_fd);
//         exit(EXIT_SUCCESS);
//     }

//     // Parent process
//     close(pipe_fds[0]); // Close both ends of the pipe
//     close(pipe_fds[1]);

//     // Wait for both child processes to finish
//     waitpid(left_pid, NULL, 0);
//     waitpid(right_pid, NULL, 0);
// }

void	runrun(ast_node *root, int input_fd, int output_fd)
{

   if (root == NULL) {
        return;
    }

	if(root->type == AST_ARG)
	{
		printf("%s   I:%d   O: %d\n", root->value,input_fd,output_fd);
		// puts("args");
		// execute_command(root, input_fd, output_fd);
	}
	if(root->type == AST_PIPE)
	{
		printf("%s   I:%d   O: %d\n", root->value,input_fd,output_fd);
		// puts("pipe");
		//execute_pipe(root, input_fd, output_fd);
	}
	if(root->type == AST_REDIN)
	{
		printf("%s   I:%d   O: %d\n", root->value,input_fd,output_fd);
		 puts("IN");
		// execute_redir_input(root, input_fd, output_fd);
	}
	if(root->type == AST_REDOUT)
	{
		printf("%s   I:%d   O: %d\n", root->value,input_fd,output_fd);
		 puts("OUT");
		// execute_redir_output(root, input_fd, output_fd);
	}

	if (root->type == AST_PIPE) {
        // for pipe nodes, input_fd is the read end of the pipe,
        // and output_fd is the write end of the pipe
		puts("Pipe\n");
        runrun(root->right, input_fd, STDOUT_FILENO);
        runrun(root->left, STDIN_FILENO, output_fd);
    } else {
        runrun(root->left, input_fd, STDOUT_FILENO);
        runrun(root->right, STDIN_FILENO, output_fd);
    }


}


