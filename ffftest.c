#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct Node {
    char* command;
    int numArguments;
    char** arguments;
    char* inputFile;
    char* outputFile;
    struct Node* left;
    struct Node* right;
} Node;

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

void executeNode(Node* node) {
    int inputFd = STDIN_FILENO;
    int outputFd = STDOUT_FILENO;

    if (node->inputFile != NULL) {
        inputFd = open(node->inputFile, O_RDONLY);
        if (inputFd < 0) {
            perror("Error opening input file");
            exit(1);
        }
    }

    if (node->outputFile != NULL) {
        outputFd = open(node->outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outputFd < 0) {
            perror("Error opening output file");
            exit(1);
        }
    }

    if (node->left != NULL) {
        int pipefd[2];
        if (pipe(pipefd) < 0) {
            perror("Error creating pipe");
            exit(1);
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Error forking process");
            exit(1);
        } else if (pid == 0) {
            // Child process
            close(pipefd[0]); // Close the read end of the pipe
            dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe

            // Execute the left node (command)
            execvp(node->left->command, node->left->arguments);
            perror("Error executing command");
            exit(1);
        } else {
            // Parent process
            close(pipefd[1]); // Close the write end of the pipe
            dup2(pipefd[0], STDIN_FILENO); // Redirect stdin from the pipe
        }
    }

    if (node->right != NULL) {
        // Execute the right node (command)
        execvp(node->right->command, node->right->arguments);
        perror("Error executing command");
        exit(1);
    }

    // Execute the command in the current node
    execvp(node->command, node->arguments);
    perror("Error executing command");
    exit(1);
}

void executeAST(Node* root) {
    if (root == NULL) {
        return;
    }

    int status;
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error forking process");
        exit(1);
    } else if (pid == 0) {
        // Child process
        executeNode(root);
    } else {
        // Parent process
        waitpid(pid, &status, 0);
    }
}

int main() {
    // Sample usage
    char*** commands = malloc(2 * sizeof(char**));
    commands[0] = malloc(4 * sizeof(char*));
    commands[0][0] = "ls";
    commands[0][1] = "-l,";
    commands[0][2] = "-a";
    commands[0][3] = NULL;
    commands[1] = NULL;

    Node* root = buildast(commands, 1);
    executeAST(root);

    // Cleanup
    free(root);

    return 0;
}
