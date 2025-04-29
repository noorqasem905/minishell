/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:48:10 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/29 20:25:59 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printf_split(char *str, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("%2%s%s\n",str, split[i]);
		i++;
	}
}

int     handle_here_doc(char *temp)
{
    int     i;
    int     err_after;
    int     is_it_correct;

    i = 2;
    err_after = -3;
    is_it_correct = 0;
    while (temp[i])
    {
        if (temp[i] == '<' || temp[i] == '>')
        {
            if (err_after == 0)
                return (-8);
            return (-1);
        }
        else if (temp[i] != ' ' && temp[i] != '>' && temp[i] != '<')
            err_after = 0;
        i++;
    }
    return (err_after);    
}

int get_free_filename(char **file_loc, char *new_fullpath)
{
    char    *new_file_loc;
    char    *temp;
    int     i;

    i = 0;
    *file_loc = ft_strdup(new_fullpath);
    while (access(*file_loc, F_OK) == 0)
    {
        temp = ft_itoa(i);
        if (temp == NULL)
            return (-1);
        new_file_loc = ft_strjoin(*file_loc, temp);
        if (!new_file_loc)
        {
            free(temp);
            free(*file_loc);
            return (-1);
        }
        free(temp);
        free(*file_loc);
        *file_loc = new_file_loc;
        i++;
    }
    return (0);
}

int     openfile_heredoc(int *fd, char **file_loc)
{
    char    *new_file_loc;
    char    *temp;
    int     i;
    
    if(get_free_filename(file_loc, "/tmp/minishell_heredoc"))
    {
        perror("malloc");
        return (-1);
    }
    *fd = open(*file_loc, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (*fd < 0)
    {
        perror("open");
        free(*file_loc);
        return (-1);
    }
    if (*file_loc)
    {
        free(*file_loc);
        *file_loc = NULL;
    }
    return (*fd);
}

int     dbg_heredoc(char *input, int *fd, char ***input_split, char **file_loc)
{
    int     check_error;
    char	*temp;

    temp = ft_strnstr(input, "<<", ft_strlen(input));
    if (!temp)
    {
        ft_printf("%2no here doc\n");
        return (0);
    }
    (*fd) = openfile_heredoc(fd, file_loc);
    if ((*fd) < 0)
        return (-1);
    check_error = handle_here_doc(temp);
    if (check_error < 0 && check_error != -8)
    {
        printf("error here doc\n");
        return (-1);
    }
    *input_split = ft_mult_split(temp, " <");
    if (!input_split)
        return (-1);
    return (0);
}

int     implement_heredoc(int *fd, char **input, int original_stdout)
{
    char    *here_doc;
    size_t  len;

    while ((here_doc = get_next_line(STDIN_FILENO)) != NULL)
    {
        len = ft_strlen(here_doc);
        if (len > 0 && here_doc[len - 1] == '\n')
            here_doc[len - 1] = '\0';
        if (ft_strcmp(here_doc, input[0]) == 0)
        {
            free(here_doc);
            break;
        }
        dup2((*fd), STDOUT_FILENO);
        printf("%s\n", here_doc);
        dup2(original_stdout, STDOUT_FILENO);
        free(here_doc);
    }
    return (0);
}

int     heredoc(char *temp)
{
    char    *file_loc;
    char    *here_doc;
    char    **input;
    size_t  len;
    int     fd[2];

    if(dbg_heredoc(temp, &fd[1], &input, &file_loc))
    {
        printf("error here doc\n");
        return (-1);
    }
    fd[0] = dup(STDOUT_FILENO);
    if (fd[0] == -1)
    {
        perror("dup");
        close(fd[1]);
        return (-1);
    }
    // implement_heredoc(&fd[1], input, fd[0]);
    // unlink(file_loc);
    close(fd[1]);
    close(fd[0]);
    frees_split(input);
    return (0);
}

// # include <readline/readline.h>
// # include <readline/history.h>
// int main(int argc, char *argv[], char **robo_env)
// {
//     // char    **input;
//     char	*temp = "ls << exit";
//     heredoc(temp);

//     // int     fd;
//     // fd = open("/tmp/minishell_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
//     // fd = openfile_heredoc(&fd);
//     // if (fd < 0)
//     //     return (-1);
//     // if(dbg_heredoc(temp, &fd, &input))
//     // {
//     //     printf("error here doc\n");
//     //     return (-1);
//     // }
//     // Done
//     // char *here_doc;
//     // int original_stdout = dup(STDOUT_FILENO);
//     // if (original_stdout == -1)
//     // {
//     //     perror("dup");
//     //     close(fd);
//     //     return (-1);
//     // }
//     // printf("here doc: %d\n", fd);
//     // while ((here_doc = get_next_line(STDIN_FILENO)) != NULL)
//     // {
//     //     size_t len = ft_strlen(here_doc);
//     //     if (len > 0 && here_doc[len - 1] == '\n')
//     //         here_doc[len - 1] = '\0';
//     //     if (ft_strcmp(here_doc, input[0]) == 0)
//     //     {
//     //         free(here_doc);
//     //         break;
//     //     }
//     //     dup2(fd, STDOUT_FILENO);
//     //     printf("%s\n", here_doc);
//     //     dup2(original_stdout, STDOUT_FILENO);
//     //     free(here_doc);
//     // }
//     // while ((here_doc = readline("> ")) != NULL)
//     // {
//     //     if (ft_strcmp(here_doc, input[0]) == 0)
//     //     {
//     //         free(here_doc);
//     //         break;
//     //     }
//     //     dup2(fd, STDOUT_FILENO);
//     //     printf("%s\n", here_doc);
//     //     dup2(original_stdout, STDOUT_FILENO);
//     //     free(here_doc);
//     // }
//     // close(fd);
//     // close(original_stdout);
//     // frees_split(input);
// }
/*
here doc

formula << exit
> ls
> ls -l
> ls -a
> exit
RoboShell>

step 1: find the here doc formula
step 2: find the exit if no error and no here doc
step 3: find the here doc are correct
step 4: do the here doc
*/