#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int size = 2;
    int pipe_fd2[size][2];
    pid_t pid;
    int i = 0;

    // Create pipes
    for (i = 0; i < size; i++)
    {
        if (pipe(pipe_fd2[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < size; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) 
        {
            if (i != 0)
            {
                if (dup2(pipe_fd2[i - 1][0], STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            if (i != size - 1)
            {
                if (dup2(pipe_fd2[i][1], STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            for (int j = 0; j < size; j++)
            {
                close(pipe_fd2[j][0]);
                close(pipe_fd2[j][1]);
            }

            if (i == 0)
            {
                char *cmd1 = "/usr/bin/ls";
                char *args1[] = {"ls", NULL};
                execve(cmd1, args1, NULL);
            }
            else if (i == 1)
            {
                char *cmd2 = "/usr/bin/grep";
                char *args2[] = {"grep", ".c", NULL};
                execve(cmd2, args2, NULL);
            }
            // else if (i == 2)
            // {
            //     char *cmd3 = "/usr/bin/ls";
            //     char *args3[] = {"ls", "-l", NULL};
            //     execve(cmd3, args3, NULL);
            // }
            // else if (i == 3)
            // {
            //     char *cmd3 = "/usr/bin/wc";
            //     char *args3[] = {"wc", "-l", NULL};
            //     execve(cmd3, args3, NULL);
            // }
            // else if (i == 4)
            // {
            //     char *cmd3 = "/usr/bin/ls";
            //     char *args3[] = {"ls", "-l", NULL};
            //     execve(cmd3, args3, NULL);
            // }

            perror("execve");
            exit(EXIT_FAILURE);
        }
    }


    for (int j = 0; j < size ; j++)
    {
        close(pipe_fd2[j][0]);
        close(pipe_fd2[j][1]);
    }

    for (i = 0; i < size; i++)
    {
        wait(NULL);
    }
    return 0;
}