/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulatething.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ychair <ychair@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:28:28 by ychair            #+#    #+#             */
/*   Updated: 2023/10/05 04:39:48 by ychair           ###   ########.fr       */
=======
/*   By: ychair <ychair@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:28:28 by ychair            #+#    #+#             */
/*   Updated: 2023/09/04 00:22:35 by ychair           ###   ########.fr       */
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
/*                                                                            */
/* ************************************************************************** */


<<<<<<< HEAD

=======
#include "../../include/minishell.h"
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
<<<<<<< HEAD
#include <stdlib.h>
#include <stdio.h>
#include "../../include/minishell.h"
#include "../../include/env.h"

char	**split(char *raw_cmd, char *limit)
=======


static char	**split(char *raw_cmd, char *limit)
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
{
	char	*ptr = NULL;
	char	**cmd = NULL;
	size_t	idx = 0;

	// split sur les espaces
	ptr = strtok(raw_cmd, limit);

	while (ptr) {
		cmd = (char **)realloc(cmd, ((idx + 1) * sizeof(char *)));
		cmd[idx] = strdup(ptr);
		ptr = strtok(NULL, limit);
		++idx;
	}
	// On alloue un element qu'on met a NULL a la fin du tableau
	cmd = (char **)realloc(cmd, ((idx + 1) * sizeof(char *)));
	cmd[idx] = NULL;
	return (cmd);
}

static void	free_array(char **array)
{
	for (int i = 0; array[i]; i++) {
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

char	*get_absolute_path(char **cmd)
{
	char	*path = strdup(getenv("PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;

	if (path == NULL) // si le path est null, on cree un path
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");

	// si cmd n'est pas le chemin absolue, on cherche le chemin absolue du
	// binaire grace a la variable d'environment PATH
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0) {

		// On split le path pour verifier ou ce trouve le binaire
		path_split = split(path, ":");
		free(path);
		path = NULL;

		// On boucle sur chaque dossier du path pour trouver l'emplacement du binaire
		for (int i = 0; path_split[i]; i++) {
			// alloc len du path + '/' + len du binaire + 1 pour le '\0'
			bin = (char *)calloc(sizeof(char), (strlen(path_split[i]) + 1 + strlen(cmd[0]) + 1));
			if (bin == NULL)
				break ;

			// On concat le path , le '/' et le nom du binaire
			strcat(bin, path_split[i]);
			strcat(bin, "/");
			strcat(bin, cmd[0]);

			// On verfie l'existence du fichier et on quitte la boucle si access
			// renvoi 0
			if (access(bin, F_OK) == 0)
				break ;

			// Nous sommes des gens propre :D

		}
		free_array(path_split);
	}
	return (bin);
}
<<<<<<< HEAD



int checkbuilt(Node *node)
{
    if(strcmp(node->command,"echo") == 0)
        return (1);
    if(strcmp(node->command,"cd") == 0)
        return (2);
    if(strcmp(node->command,"pwd") == 0)
        return (3);
    if(strcmp(node->command,"export") == 0)
        return (4);
    if(strcmp(node->command,"unset") == 0)
        return (5);
    if(strcmp(node->command,"env") == 0)
        return (6);
    if(strcmp(node->command,"exit") == 0)
        return (7);
    return (0);
}

char **execbuiltin(Node *node,int checkbuiltin,char **env)
{
    int i;

    i = 0;
    // (void)node;
    if(checkbuiltin == 1)
    {
        // printf("%s\n",node->arguments[0]);
        while(node->arguments[i])
            ft_echo(node->arguments[i++],0,1);
    }
    if(checkbuiltin == 2)
    {
        // printf("%s\n",node->arguments[0]);
           ft_cd(node->arguments[0],env);
    }
    if(checkbuiltin == 3)
    {
            ft_pwd();
    }
    if(checkbuiltin == 4)
    {
            ft_export(env, node->arguments[0]);
    }
    if(checkbuiltin == 5)
     {
            env = ft_unset(node->arguments[0], env);
            
     }
     if(checkbuiltin == 6)
     {
        ft_env(env, 1);
       
     }
    if(checkbuiltin == 7)
    {
           exit(0);
    }
     
  return (env);
}

void     ft_heredocs(Node *node)
{
     if (node == NULL) {
        return;
    }
    char *delimiter = node->inputFile;
    char *line = NULL;
    size_t line_size = 0;

    //  while (1) {
           getline(&line, &line_size, stdin);


            // Check if the line matches the delimiter
            if (strcmp(line, delimiter) == 0) {
                puts("lol");//     break; // Exit the loop when the delimiter is encountered
            }

            // Process the line as needed, you can save it to a file or use it in your shell logic
            // For now, let's just print it
            printf("Here document line: %s", line);
        // }
            free(line);
}


char **executeCommand(Node *node, int in_fd, int out_fd,char **env) {
     int file_fd;
     int  checkbuiltin;
	 pid_t pids;
     
=======
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

void executeCommand(Node* node, int in_fd, int out_fd) {
     int file_fd;
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
    // Create an array to hold the command and arguments
    char** args = (char**)malloc((node->numArguments + 2) * sizeof(char*));
    args[0] = node->command;

    for (int i = 0; i < node->numArguments; i++) {
        args[i + 1] = node->arguments[i];
    }
    args[node->numArguments + 1] = NULL;

<<<<<<< HEAD
    
    // Set the input/output file descriptors based on redirection
    if (node->inputFile != NULL && node->app !=2) {
        // Redirect input from a file
    	file_fd = open(node->inputFile, O_RDONLY);
=======
    // Set the input/output file descriptors based on redirection
    if (node->inputFile != NULL) {
        // Redirect input from a file
        int file_fd = open(node->inputFile, O_RDONLY);
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
        dup2(file_fd, STDIN_FILENO);
        close(file_fd);
    } else if (in_fd != STDIN_FILENO) {
        // Redirect input from a pipe
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
<<<<<<< HEAD
    if (node->inputFile != NULL && node->app ==2)
    {
        //FORK FILETMP!>
        ft_heredocs(node);
    }
    if (node->outputFile != NULL) {
        // Redirect output to a file
         
=======

    if (node->outputFile != NULL) {
        // Redirect output to a file
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
        if(node->app == 1)
            file_fd = open(node->outputFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            file_fd = open(node->outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(file_fd, STDOUT_FILENO);
        close(file_fd);
<<<<<<< HEAD
    }
	else if (out_fd != STDOUT_FILENO) {
       
        // Redirect output to a pipemaa
        dup2(out_fd, STDOUT_FILENO);
         
        close(out_fd);
        
    }
    checkbuiltin = checkbuilt(node);
    if(checkbuiltin != 0){
       env = execbuiltin(node,checkbuiltin,env);
         
    }
    else {
			pids = fork();
            if (pids == -1) {
                perror("Fork failed");
                exit(1);
            } 
            else if (pids == 0) {
                // Child process
       			execve(get_absolute_path(args),args,NULL);
				exit(0);
            }
            else{
                    // printf("UWU PARENT %d\n",pids);
                    // wait(NULL);
                     int status;
                    waitpid(pids, &status, 0); // Wait for the specific child process
                  
                }
	}
    
   	free(args);
     
    return (env);
}

// void executeAST(Node* node, int in_fd, int out_fd,char **env) {
   
    

//     int pipe_fds[2];
//     pid_t pid;
//     int original_stdin;
//     int original_stdout;

//     original_stdin = dup(STDIN_FILENO);
//     original_stdout = dup(STDOUT_FILENO);
//     if (node == NULL) {
//         return;
//     }
//     if (strcmp(node->command, "|") == 0) {
//         // Create a pipe for communication between child processes
//         if (pipe(pipe_fds) == -1) {
//             perror("Pipe creation failed");
//             exit(1);
//         }

//         // Fork a child process to execute the left side of the pipe
//         pid = fork();
//         if (pid == -1) {
//             perror("Fork failed");
//             exit(1);
//         } else if (pid == 0) {
//             // Child process
//             close(pipe_fds[0]); // Close the read end of the pipe
                     
//             // executeAST(node->left, in_fd, pipe_fds[1],env);
//             executeCommand(node->left, in_fd, pipe_fds[1],env);
//             exit(0);
//         }
//           int status;
//                     waitpid(pid, &status, 0); // Wait for the specific child process
//                     if (WIFEXITED(status)) {
//                         close(pipe_fds[1]); // Close the write end of the pipe
//                         executeAST(node->right, pipe_fds[0], out_fd,env);
//                         close(pipe_fds[0]); // Close the read end of the pipe
//                     }             
//     } else {
//             	executeCommand(node, in_fd, out_fd,env);
//     }
//     dup2(original_stdin, STDIN_FILENO);
//     dup2(original_stdout, STDOUT_FILENO);
//     close(original_stdin);
//     close(original_stdout);
// }

///FALLLSEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

char ** executeAST(Node* node, int in_fd, int out_fd, char** env) {
    int pipe_fds[2];
    int original_stdin;
    int original_stdout;

    original_stdin = dup(STDIN_FILENO);
    original_stdout = dup(STDOUT_FILENO);

    if (node == NULL) {
        return(NULL);
    }

    if (strcmp(node->command, "|") == 0) {
        // Create a pipe for communication between processes
=======
    } else if (out_fd != STDOUT_FILENO) {
        // Redirect output to a pipe
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }

    // Execute the command
   // execvp(args[0], args);
//    printf("%s\n%s\n",get_absolute_path(args),args[0]);
       execve(get_absolute_path(args),args,NULL);
    // If execvp returns, it means an error occurred
   perror("Command execution failed");
   exit(1);
   free(args);
}

void executeAST(Node* node, int in_fd, int out_fd) {
    if (node == NULL) {
        return;
    }

    int pipe_fds[2];
    pid_t pid;

    if (strcmp(node->command, "|") == 0) {
        // Create a pipe for communication between child processes
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
        if (pipe(pipe_fds) == -1) {
            perror("Pipe creation failed");
            exit(1);
        }

<<<<<<< HEAD
        // Execute the left side of the pipe
        executeAST(node->left, in_fd, pipe_fds[1], env);
        
        // Close the write end of the pipe in the parent process
        close(pipe_fds[1]);

        // Redirect input for the right side of the pipe
        dup2(pipe_fds[0], STDIN_FILENO);
        close(pipe_fds[0]);

        // Execute the right side of the pipe
        executeAST(node->right, STDIN_FILENO, out_fd, env);
    } else {
        // No pipe, execute the command
        
        env = executeCommand(node, in_fd, out_fd, env);
        
    }

    // Restore original stdin and stdout
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);

    close(original_stdin);
    close(original_stdout);
     
     return (env);
}
=======
        // Fork a child process to execute the left side of the pipe
        pid = fork();
        if (pid == -1) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process
            close(pipe_fds[0]); // Close the read end of the pipe
            executeAST(node->left, in_fd, pipe_fds[1]);
            exit(0);
        }

        // Parent process continues to execute the right side of the pipe
        close(pipe_fds[1]); // Close the write end of the pipe
        executeAST(node->right, pipe_fds[0], out_fd);
        close(pipe_fds[0]); // Close the read end of the pipe

        // Wait for the child process to finish
        wait(NULL);
    } else {
        if (node->right != NULL && strcmp(node->right->command, "|") == 0) {
            // Create a pipe for communication between child processes
            if (pipe(pipe_fds) == -1) {
                perror("Pipe creation failed");
                exit(1);
            }
            // Fork a child process to execute the current command
            pid = fork();
            if (pid == -1) {
                perror("Fork failed");
                exit(1);
            } else if (pid == 0) {
                // Child process
                close(pipe_fds[0]); // Close the read end of the pipe
                executeCommand(node, in_fd, pipe_fds[1]);
                exit(0);
            }

            // Parent process continues to execute the right side of the pipe
            close(pipe_fds[1]); // Close the write end of the pipe
            executeAST(node->right, pipe_fds[0], out_fd);
            close(pipe_fds[0]); // Close the read end of the pipe

            // Wait for the child process to finish
            wait(NULL);
        } else {
            // Execute a single command
            executeCommand(node, in_fd, out_fd);
        }
    }
}
>>>>>>> 26f2e0fef931109ebf20856787daf6b93424e742
