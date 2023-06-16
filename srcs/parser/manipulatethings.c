/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulatethings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:14:34 by ychair            #+#    #+#             */
/*   Updated: 2023/06/16 07:50:38 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <errno.h>

void executeCommand(Node* node) {
    // tab args for execve,la command en [0] 
    char** args = (char**)malloc((node->numArguments + 2) * sizeof(char*));
    args[0] = node->command;
    int i;

    i=0;
    while(i < node->numArguments) {
        args[i + 1] = node->arguments[i];
        i++;
    }
    args[node->numArguments + 1] = NULL;

    // File redirection a verifier !!!!!!!
    // if (node->inputFile != NULL) {
    //     int fd = open(node->inputFile, O_RDONLY);
    //     if (fd < 0) {
    //         perror("Error opening input file");
    //         //exit(1);
    //     }
    //     dup2(fd, STDIN_FILENO);
    //     close(fd);
    // }
    // File redirection a verifier !!!!!!!
    // if (node->outputFile != NULL) {
    //     int fd = open(node->outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    //     if (fd < 0) {
    //         perror("Error opening output file");
    //         //exit(1);
    //     }
    //     dup2(fd, STDOUT_FILENO);
    //     close(fd);
    // }

    // Execute the command
    if (execvp(node->command, args) < 0) {
        perror("Error executing command");
    }
}

void executeAST(Node* node, int in_fd, int out_fd) {
    if (node == NULL) {
        return;
    }
    //si node right alors on a operateur .
    if (node->right != NULL) {
        int pipefd[2];
        if (pipe(pipefd) < 0) {
            perror("Error creating pipe");
            //exit(1);
        }

        pid_t child1, child2;
        child1 = fork();
        if (child1 < 0) {
            perror("Error forking child process");
            //exit(1);
        } else if (child1 == 0) {
            // Child 1: Executes the left child of the pipe node
            close(pipefd[0]); // Close unused read end
            dup2(in_fd, STDIN_FILENO); // Replace stdin with input file descriptor
            dup2(pipefd[1], STDOUT_FILENO); // Replace stdout with write end of the pipe
            close(pipefd[1]); // Close write end of the pipe
            executeAST(node->left, STDIN_FILENO, pipefd[1]); // Recursively execute left child with new input and output file descriptors
            //exit(0);
        }

        child2 = fork();
        if (child2 < 0) {
            perror("Error forking child process");
            //exit(1);
        } else if (child2 == 0) {
            // Child 2: Executes the right child of the pipe node
            close(pipefd[1]); // Close unused write end
            dup2(pipefd[0], STDIN_FILENO); // Replace stdin with read end of the pipe
            close(pipefd[0]); // Close read end of the pipe
            executeAST(node->right, pipefd[0], out_fd); // Recursively execute right child with new input and output file descriptors
            //exit(0);
        }

        // Parent process: Wait for both children to finish
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(child1, NULL, 0);
        waitpid(child2, NULL, 0);
    } else {
        // No pipes, handle file redirection and execute the command
        if (node->inputFile != NULL) {
            int fd = open(node->inputFile, O_RDONLY);
            if (fd < 0) {
                perror("Error opening input file");
                //exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        } else if (in_fd != STDIN_FILENO) {
            dup2(in_fd, STDIN_FILENO);
        }

        if (node->outputFile != NULL) {
            int fd;
            if (strcmp(node->command, ">>") == 0) {
                fd = open(node->outputFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
            } else {
                fd = open(node->outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            if (fd < 0) {
                perror("Error opening output file");
                //exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (out_fd != STDOUT_FILENO) {
            dup2(out_fd, STDOUT_FILENO);
        }

       executeCommand(node);
        //exit(0);
    }
}