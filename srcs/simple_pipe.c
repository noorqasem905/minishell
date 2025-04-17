#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/minishell.h"
#include <string.h>
#include <sys/wait.h>

int main()
{
    int size = 3;
    int pipe_fd2[size][2];

    pid_t pid1, pid2, pid3;
    int i = 0;
    int j = 0;

    while (i < size)
    {
        if (pipe(pipe_fd2[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    pid1 = fork();        
    if (pid1 < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    if (pid1 == 0) {
        close(pipe_fd2[0][1]); // Close unused write end
        close(pipe_fd2[1][0]); // Close read end
        close(pipe_fd2[2][0]); // Close read end
        close(pipe_fd2[2][1]); // Close write end        
        int x;
        read(pipe_fd2[0][0], &x, sizeof(x)); // Read from pipe
        x += 5;
        write(pipe_fd2[1][1], &x, sizeof(x)); // Write to pipe

        close(pipe_fd2[0][0]); // Close read end
        close(pipe_fd2[1][1]); // Close write end
        return (0);
    }
    pid2 = fork();
    if (pid2 < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    if (pid2 == 0)
    {
        close(pipe_fd2[0][0]); // Close read end
        close(pipe_fd2[0][1]); // Close read end
        close(pipe_fd2[1][1]); // Close write end
        close(pipe_fd2[2][0]); // Close read end
        int x;
        read(pipe_fd2[1][0], &x, sizeof(x)); // Read from pipe
        x += 5;
        write(pipe_fd2[2][1], &x, sizeof(x)); // Write to pipe

        close(pipe_fd2[1][0]); // Close read end
        close(pipe_fd2[2][1]); // Close write end
        return (0);
    }
        close(pipe_fd2[0][0]); // Close read end
        close(pipe_fd2[1][0]); // Close read end
        close(pipe_fd2[1][1]); // Close write end
        close(pipe_fd2[2][1]); // Close read end
        int x = 0;
        write(pipe_fd2[0][1], &x, sizeof(x)); // Write to pipe
        read(pipe_fd2[2][0], &x, sizeof(x)); // Read from pipe
        printf("x: %d\n", x);
        close(pipe_fd2[0][1]); // Close read end
        close(pipe_fd2[2][0]); // Close write end
        waitpid(pid1, NULL, 0); // Wait for child process to finish
        waitpid(pid2, NULL, 0); // Wait for child process to finish
        return (0);


}