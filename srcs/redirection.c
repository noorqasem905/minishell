/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:00:09 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/22 20:33:35 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>

int check_redirection(char *input)
{
    int i = 0;
    int is_pipe = 0;
    int return_value = 0;
    while (input[i])
    {
        if (input[i] == '>' && is_pipe == 0)
        {
            if (input[i + 1] == '>')
                return (1);
            else
                return (2);
        }
        else if (input[i] == '<' || is_pipe == 1)
        {
            if (input[i] == '<')
            {
                return_value = 3;
                is_pipe = 1;
            }
            else if (input[i] == '>')
                return (4);
        }
        i++;
    }
    return (return_value);
}

int check_redirection_mult(char *input, int type)
{
    int mult = 0;
    int mult_2 = 0;
    int i = 0;
    int handle = 0;
    int conflect = 0;
    int is_enter = 0;
    int is_file = 0;
    while (input[i])
    {
        if (input[i] == '<')
        {
            mult++;
            conflect++;
            if (is_enter > 0 && is_file == 0)
                return (-1);
            is_enter = 1;
            is_file = 0;
            if (input[i + 1] == '<' && handle == 0)
            {
                i++;
                handle = 1;
            }
            if (input[i + 1] == '>')
                return (-1);
        }
        else if (input[i] == '>')
        {
            mult_2++;
            conflect++;
            if (is_enter > 0 && is_file == 0)
                return (-1);
            is_enter = 2;
            is_file = 0;
            if (input[i + 1] == '>' && handle == 0)
            {
                i++;
                handle = 1;
            }
            if (input[i + 1] == '<')
                return (-1);
        }
        else if (input[i] != ' ' && input[i] != '>' && input[i] != '<')
        {
            conflect = 0;
            mult_2 = 0;
            mult = 0;
            is_enter = 0;
            is_file = 1;
        }
        if (mult > 1 || mult_2 > 1 || conflect > 1)
            return (-1);
        i++;
    }
    if (is_enter > 0 && is_file == 0)
            return (-1);
    if (mult > 1 || mult_2 > 1 || conflect > 1) 
        return (-1);
    return (0);
}


int main()
{
    char *inter = "ls here_doc.c s  <a ";
    char *temp = NULL;
    char *temp2 = NULL;
    int redirection_type = check_redirection(inter);
    dprintf(2, "Redirection type: %d\n", redirection_type);
    int mult = check_redirection_mult(inter, redirection_type);
    if (mult == -1)
    {
        dprintf(2, "Error: Multiple redirections\n");
        return (-1);
    }
    if (redirection_type != 2)
    {
        temp = ft_strfchr(inter, '<');
        temp2 = ft_strchr(inter, '<');
    }
    else
    {
        temp = ft_strfchr(inter, '>');
        temp2 = ft_strchr(inter, '>');
    }
    dprintf(2, "%s\n", temp);
    dprintf(2, "%s\n", temp2);
    free(temp);
    // char *temp = NULL;
    // char file;
    // char **split = ft_split(inter, '<');
    // char **split = ft_split(inter, ' ');
    // int fd = open(split[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // int fd_read = open(split[1], O_RDONLY);
    // if (fd == -1)
    // {
    //     perror("open");
    //     return (-1);
    // }
    // if (dup2(fd, STDOUT_FILENO) == -1)
    // {
    //     perror("dup2");
    //     close(fd);
    //     return (-1);
    // }
    // if (dup2(fd_read, STDIN_FILENO) == -1)
    // {
    //     perror("dup2");
    //     close(fd);
    //     return (-1);
    // }
    
    // char *cmd = "/usr/bin/ls";
    // char *ags[] = {cmd, NULL};

    // dprintf(2, "Executing command: %s\n", split[0]);
    // if (execve(cmd,ags , NULL) == -1)
    // {
    //     perror("execve");
    //     return (-1);
    // }
    // close(fd);
    return (0);
}
    /* Note */
/*                          
// i have to handle all cases of pipe <> else if eveything is ok


















 */