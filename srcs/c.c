#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"

int main() {
    char *input;

    while ((input = readline(">> ")) != NULL) {
        if (*input) {
            add_history(input);
        }
        printf("You entered: %s\n", input);
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }
        free(input); // Free memory allocated by readline
    }

    return 0;
}