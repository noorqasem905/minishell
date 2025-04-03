/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:32:33 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/03 22:38:23 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/printf/ft_printf.h"

int read_input(char **input)
{
    size_t  length;
    char *read;

    ft_printf("Roboshell> ");
    read = get_next_line(0);
    if (read == NULL)
    {
        free(read);
        return (-1);
    }
    length = ft_strlen(read);
    (*input) = ft_strdup(read);
    if ((*input) == NULL)
    {
        free(read);
        return (-1);
    }
    free(read);
    (*input)[length - 1] = '\0';
    return (0);
}

int main(int argc, char *argv[])
{
    t_cmd *cmd;
    char *str = "hello";

    cmd = malloc(sizeof(t_cmd));
    // insertend(&cmd->word , str, 0);
    // printf("cmd->word: %s\n", (char *)cmd->word->content);
    // malloc for word or use linked list i think it's better
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
        // cmd->word = ft_split(input, ' ');
        // frees_split(cmd->word);
        // cmd->word = malloc(sizeof(char *) * 2);
    
        // if (cmd->word == NULL)
        // {
        //     free(input);
        //     return (-1);
        // }
        // ft_printf("Command: %s\n", cmd->word[0]);
        free(input);
    }
    return 0;
}
