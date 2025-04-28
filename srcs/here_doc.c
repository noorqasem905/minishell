/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:48:10 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/28 21:45:08 by nqasem           ###   ########.fr       */
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

int	here_doc(void)
{
    char    **input;
    char	*temp;
    int     fd;
    int     check;
    int     i;

    i = 0;
    check = 0;
    temp = ft_strmchr("ls << exit", "<<");
    ft_strcmp(temp, "<<");
    input = ft_mult_split(temp, "<<");
    printf_split("here doc: ", input);
    // check = 
    return (0);
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
# include <readline/readline.h>
# include <readline/history.h>
int main(int argc, char *argv[], char **robo_env)
{
    char    **input;
    char	*temp;
    int     fd;
    int     check;
    int     i;

    i = 0;
    check = 0;
    fd = open("/tmp/minishell_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (ft_strnstr("ls <<exit", "<<", 10))
        temp = ft_strnstr("ls <<exit<", "<<", 20);
    else
    {
        printf("no here doc\n");
        return (0);
    }
    int check_error = handle_here_doc(temp);
    if (check_error < 0 && check_error != -8)
    {
        printf("error here doc\n");
        return (-1);
    }
    input = ft_mult_split(temp, " <");
    printf_split("here doc:", input);
    char *here_doc;
    int original_stdout = dup(STDOUT_FILENO);
    if (original_stdout == -1)
    {
        perror("dup");
        close(fd);
        return (-1);
    }
    while ((here_doc = readline("> ")) != NULL)
    {
        if (ft_strcmp(here_doc, input[0]) == 0)
        {
            free(here_doc);
            break;
        }
        dup2(fd, STDOUT_FILENO);
        printf("%s\n", here_doc);
        dup2(original_stdout, STDOUT_FILENO);
        free(here_doc);
    }
    while ((here_doc = readline("> ")) != NULL)
    {
        if (ft_strcmp(here_doc, input[0]) == 0)
        {
            free(here_doc);
            break;
        }
        dup2(fd, STDOUT_FILENO);
        printf("%s\n", here_doc);
        dup2(original_stdout, STDOUT_FILENO);
        free(here_doc);
    }
    close(fd);
    close(original_stdout);
    unlink("/tmp/minishell_heredoc");
    if (check_error == -8)
    {
        printf("error here doc After\n");
        return (-1);
    }
}
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