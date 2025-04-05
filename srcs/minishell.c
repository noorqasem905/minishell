/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:32:33 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/05 21:31:29 by nqasem           ###   ########.fr       */
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

int save_data(char **input, t_cmd **cmd, int *flag)
{
    char **temp;
    int size;
    int iterator;

    *flag = 0;
    temp = ft_split(*input, ' ');
    if (temp == NULL)
        return (-1);
    size = ft_2dlen(temp);
    (*cmd)->word = NULL;
    iterator = -1;
    while (++iterator < size)
        if (temp[iterator] != NULL)
        {
            insertend(&((*cmd)->word), temp[iterator], flag);
            if (*flag == 12)
                break;
        }
    free(*input);
    frees_split(temp);
    return (*flag);
}
int main(int argc, char *argv[])
{
    t_cmd *cmd;
    char *str = "hello";
    int         size;
    int         iterator;
    int         flag;

    cmd = malloc(sizeof(t_cmd));
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
        if (save_data(&input, &cmd, &flag) == -1)
        {
            perror("save_data");
            free(input);
            break;
        }
        frees(&cmd->word);
    }
    free(cmd);
    return 0;
}
