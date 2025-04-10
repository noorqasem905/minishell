#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

    // Create pipe
    if (pipe(pipe_fd) == -1) {
        // perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Save the original stdout to restore it later
    int saved_stdout = dup(STDOUT_FILENO);

    // First child: "ls -l"
    // printf("Creating first child process...\n");
    pid1 = fork();
    if (pid1 == 0) {
        // Redirect stdout to write end of pipe
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect to pipe
        close(pipe_fd[0]); // Close unused read end
        close(pipe_fd[1]); // Close write end after dup2

        // Print to screen as well before executing
        // printf("This will not be printed, as stdout is redirected to the pipe.\n");

        // Define arguments for execve
        char *cmd1 = "/bin/ls"; // Full path to ls
        char *args1[] = {"ls", "-l", NULL};
        execve(cmd1, args1, NULL); // Execute ls -l
        // perror("execve ls"); // If execve fails
        exit(EXIT_FAILURE);
    }

    // Second child: "grep txt"
    pid2 = fork();
    if (pid2 == 0) {
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);

        // Define arguments for execve
        char *cmd2 = "/usr/bin/grep"; // Full path to grep
        char *args2[] = {"grep","n.c", NULL};
        execve(cmd2, args2, NULL); // Execute grep txt
        // perror("execve grep"); // If execve fails
        exit(EXIT_FAILURE);
    }
    if (pid2 > 0) {
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);

        // Define arguments for execve
        char *cmd3 = "/usr/bin/wc"; // Full path to grep
        char *args3[] = {"wc", "-l", NULL};
        execve(cmd3, args3, NULL); // Execute grep txt
        // perror("execve grep"); // If execve fails
        exit(EXIT_FAILURE);
    }
    // Parent process: Close both ends of the pipe
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both children to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    // Restore original stdout and print the output
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    // Print a final message to confirm we're back to normal stdout
    // printf("Back to normal stdout. Output after this message will go to the terminal.\n");

    return 0;
}
    // int pipefd[2 * (MAX_CMDS - 1)]; // multiply by 2 for read and write ends