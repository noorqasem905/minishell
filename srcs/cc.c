#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/minishell.h"
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    int pipe_fd2[2 * 3];
    pid_t pid1, pid2;

    // Create pipe
    if (pipe(pipe_fd) == -1) {
        // perror("pipe");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < 3) {
        if (pipe(pipe_fd2 + i * 2) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++; // Ensure the loop increments to avoid infinite loop
    }        

    int size = 3;
    i = 0;
    while (i < size) {
        pid1 = fork();
        if (pid1 == 0) {
            // Child process
            if (i != size - 1) {
                // Redirect stdout to the write end of the current pipe
                dup2(pipe_fd2[(i * 2) + 1], STDOUT_FILENO);
            }
            if (i != 0) {
                // Redirect stdin to the read end of the previous pipe
                dup2(pipe_fd2[(i - 1) * 2], STDIN_FILENO);
            }
            // Close all pipe ends in the child process
            int j = 0;
            while (j < size) {
                close(pipe_fd2[j * 2]);
                close(pipe_fd2[(j * 2) + 1]);
                j++;
            }
            // Execute command based on the child index
            if (i == 0) {
                char *cmd1 = "/usr/bin/ls";
                char *args1[] = {"ls", "-al", NULL};
                execve(cmd1, args1, NULL);
            } else if (i == 1) {
                char *cmd2 = "/usr/bin/grep";
                char *args2[] = {"grep", ".c", NULL};
                execve(cmd2, args2, NULL);
            } else if (i == 2) {
                char *cmd3 = "/usr/bin/wc";
                char *args3[] = {"wc", "-l", NULL};
                execve(cmd3, args3, NULL);
            }
            // If execve fails
            perror("execve");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    // Close all pipe ends in the parent process
    int j = 0;
    while (j < size) {
        close(pipe_fd2[j * 2]);
        close(pipe_fd2[(j * 2) + 1]);
        j++;
    }
    // Wait for all child processes to finish
    i = 0;
    while (i < size) {
        wait(NULL);
        i++;
    }

    return 0;
}