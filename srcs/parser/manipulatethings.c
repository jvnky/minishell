/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulatethings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:14:34 by ychair            #+#    #+#             */
/*   Updated: 2023/06/16 17:39:32 by ychair           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <errno.h>
void executeCommand(Node* node, int in_fd, int out_fd) {
    char** args = (char**)malloc((node->numArguments + 2) * sizeof(char*));
    args[0] = node->command;

    for (int i = 0; i < node->numArguments; i++) {
        args[i + 1] = node->arguments[i];
    }
    args[node->numArguments + 1] = NULL;

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process

        // Set up input and output redirection based on file descriptors
        if (in_fd != STDIN_FILENO) {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }

        if (out_fd != STDOUT_FILENO) {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        // Set the PATH environment variable
        char* path = "/bin:/usr/bin"; // Adjust as per your system's paths
        setenv("PATH", path, 1);

        // Execute the command
        execvp(node->command, args);

        // If execvp returns, it means an error occurred
        perror("Command execution failed");
        exit(1);
    } else {
        // Parent process

        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);

        // Check if the child process exited normally
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0) {
                fprintf(stderr, "Child process exited with status %d\n", exit_status);
            }
        } else if (WIFSIGNALED(status)) {
            int signal_number = WTERMSIG(status);
            fprintf(stderr, "Child process terminated by signal %d\n", signal_number);
        }
    }
}


void executeAST(Node* node, int in_fd, int out_fd) {
    if (node == NULL) {
        return;
    }

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

        executeCommand(node, in_fd, out_fd);
        //exit(0);
    }
}