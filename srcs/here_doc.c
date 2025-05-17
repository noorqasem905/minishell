/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:48:10 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/15 19:06:21 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
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
 */

int		is_there_else_heredoc(char *temp)
{
	int		i;

	i = 0;
	while (temp[i])
	{
		while(temp[i] == '<' || temp[i] == '>')
			i++;
		while (isspace(temp[i]))
			i++;
		if(temp[i] == '\0' || temp[i] == '<' || temp[i] == '>')
			return (-8);
		while (temp[i] != '\0' && temp[i] != '<' && temp[i] != '>' && !isspace(temp[i]))
			i++;
		while (isspace(temp[i]))
			i++;		
	}
	return (8);
}

int	handle_here_doc(char *temp)
{
	int	i;
	int	err_after;
	int	is_it_correct;

	i = 2;
	err_after = -3;
	is_it_correct = 0;
	while (temp[i])
	{
		if (temp[i] == '<' || temp[i] == '>')
		{
			if (err_after == 0)
				return (is_there_else_heredoc(temp));
			return (-1);
		}
		else if (temp[i] != ' ' && temp[i] != '>' && temp[i] != '<')
			err_after = 0;
		i++;
	}
	return (err_after);
}

int	get_free_filename(char **file_loc, char *new_fullpath)
{
	char	*new_file_loc;
	char	*temp;
	int		i;

	i = 0;
	new_file_loc = ft_strdup(new_fullpath);
	if (!new_file_loc)
		return (-1);
	while (access(new_file_loc, F_OK) == 0)
	{
		free(new_file_loc);
		temp = ft_itoa(i);
		if (!temp)
			return (-1);
		new_file_loc = ft_strjoin(new_fullpath, temp);
		free(temp);
		if (!new_file_loc)
			return (-1);
		i++;
	}
	*file_loc = new_file_loc;
	return (0);
}

int	openfile_heredoc(int *fd, char **file_loc)
{
	if (get_free_filename(file_loc, "/tmp/minishell_heredoc"))
	{
		perror("malloc");
		if (*file_loc)
			free(*file_loc);
		return (-1);
	}
	*fd = open(*file_loc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
	{
		perror("open");
		free(*file_loc);
		return (-1);
	}
	return (*fd);
}

int	dbg_heredoc(char *input, int *fd, char ***input_split, char **file_loc)
{
	int		check_error;
	char	*temp;

	// ft_printf("%2%s\n", input);
	temp = ft_strnstr(input, "<<", ft_strlen(input));
	if (!temp)
	{
		ft_printf("%2no here doc\n");
		return (0);
	}
	check_error = handle_here_doc(temp);
	if (check_error < 0)
	{
		printf("error here doc\n");
		return (-1);
	}
	(*fd) = openfile_heredoc(fd, file_loc);
	if ((*fd) < 0)
	{
		if (*file_loc)
		free(*file_loc);
		return (-2);
	}
	*input_split = ft_mult_split(temp, " <");
	if (!*input_split)
	{
		if (*file_loc)
			free(*file_loc);
		return (-1);
	}
	return (check_error);
}

int	implement_heredoc(int *fd, char **input, int original_stdout)
{
	char	*here_doc;
	size_t	len;

	while ((here_doc = get_next_line(STDIN_FILENO)) != NULL)
	{
		len = ft_strlen(here_doc);
		if (len > 0 && here_doc[len - 1] == '\n')
			here_doc[len - 1] = '\0';
		if (ft_strcmp(here_doc, input[0]) == 0)
		{
			free(here_doc);
			break ;
		}
		dup2((*fd), STDOUT_FILENO);
		write(*fd, here_doc, len);
		write(*fd, "\n", 1);
		dup2(original_stdout, STDOUT_FILENO);
		free(here_doc);
	}
	return (0);
}

int		heredoc_mult_process(int check_error, char **file_loc, int fd[])
{
	if (check_error < 0)
    {
        printf("error here doc\n");
        if (*file_loc)
            free(*file_loc);
        return (-1);
    }
    fd[0] = dup(STDOUT_FILENO);
    if (fd[0] == -1)
    {
        perror("dup");
        close(fd[1]);
        if (*file_loc)
            free(*file_loc);
        return (-1);
    }
	return (0);
}

int		heredoc_mult(int heredoc_count, char **file_loc, char *heredoc_ptrs[])
{
	char	**input;
    int		fd[2];
    int		check_error;
    int		i = 0;

	i = 0;
	while (i < heredoc_count)
    {
        check_error = dbg_heredoc(heredoc_ptrs[i], &fd[1], &input, file_loc);
		if(heredoc_mult_process(check_error, file_loc, fd) < 0)
			return (-1);
        implement_heredoc(&fd[1], input, fd[0]);
        close(fd[1]);
        close(fd[0]);
        frees_split(input);
        if (i < heredoc_count - 1 && *file_loc)
        {
            free(*file_loc);
            *file_loc = NULL;
        }
        i++;
    }
	return (0);
}

int	heredoc(char *temp, char **file_loc, size_t size)
{
    char	*heredoc_ptrs[size];
    char	*search = temp;
    int		heredoc_count = 0;
	int		fd[2];

	while ((search = ft_strnstr(search, "<<", ft_strlen(search))))
    {
        heredoc_ptrs[heredoc_count++] = search;
        search += 2;
    }
	if (heredoc_mult(heredoc_count, file_loc, heredoc_ptrs) < 0)
		return (-1);
    return (0);
}

/* # include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char *argv[], char **robo_env)
{
	// char    **input;
	char	*temp = "cat << end ";
	dprintf(2,"%d", heredoc(temp));
} */
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
//     //         break ;
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
//     //         break ;
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