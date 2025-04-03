/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:32:33 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/03 20:41:22 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/printf/ft_printf.h"

int read_input(char **input)
{
    char *line = NULL;
    size_t  length;
    char *read;

    ft_printf("Roboshell> ");
    read = get_next_line(0);
    if (read == NULL)
    {
        free(line);
        return (-1);
    }
    length = ft_strlen(read);
    input[0] = ft_strdup(read);
    if (input[0] == NULL)
    {
        free(read);
        return (-1);
    }
    free(read);
    input[0][length - 1] = '\0';
    return (0);
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return (1);
    }
    char *input = NULL;
    while (1)
    {
        if (read_input(&input) == -1)
        {
            perror("getline");
            break;
        }
        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        ft_printf("You entered: %s\n", input);
        free(input);
    }
    return 0;
}
