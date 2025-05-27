/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:48:10 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/27 08:10:51 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <sys/types.h>
#include <signal.h>


int	dbg_heredoc(char *input, int *fd, char ***input_split, char **file_loc)
{
	int		check_error;
	char	*temp;

	temp = ft_strnstr(input, "<<", ft_strlen(input));
	if (!temp)
		return ((free_err_ret("no here doc\n", (NULL), NULL, 0)));
	check_error = handle_here_doc(temp);
	if (check_error < 0)
		return ((free_err_ret("error here doc\n", NULL, NULL, -1)));
	(*fd) = openfile_heredoc(fd, file_loc);
	if ((*fd) < 0)
		return ((free_err_ret(NULL, NULL, NULL, -2)));
	*input_split = ft_mult_split(temp, " <>");
	if (!*input_split)
		return ((free_err_ret(NULL, (void *)(*file_loc), NULL, -1)));
	return (check_error);
}

int	implement_heredoc(int *fd, char **input, int original_stdout)
{
	char	*here_doc;
	size_t	len;
	struct sigaction old_sigint;
	struct sigaction new_sigint;

	new_sigint.sa_handler = handle_heredoc_sigint;
	sigemptyset(&new_sigint.sa_mask);
	new_sigint.sa_flags = 0;
	sigaction(SIGINT, &new_sigint, &old_sigint);
	while (1)
	{
		here_doc = readline("> ");
		if (s_sig || here_doc == NULL)
		{
			free(here_doc);
			write(2,"exitting\n",10); 
			sigaction(SIGINT, &old_sigint, NULL);
			break;
		}
		if (here_doc == NULL)
			break ;
		
		len = ft_strlen(here_doc);
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
	sigaction(SIGINT, &old_sigint, NULL);
	return (0);
}


int	heredoc_mult_process(int check_error, char **file_loc, int fd[])
{
	if (check_error < 0)
		return (-1);
	fd[0] = dup(STDOUT_FILENO);
	if (fd[0] == -1)
	{
		ft_printf("%2dup\n");
		close(fd[1]);
		if (*file_loc)
			free(*file_loc);
		return (-1);
	}
	return (0);
}

int	heredoc_mult(int heredoc_count, char **file_loc, char *heredoc_ptrs[])
{
	char	**input;
	int		fd[2];
	int		check_error;
	int		i;

	i = 0;
	i = 0;
	while (i < heredoc_count)
	{
		check_error = dbg_heredoc(heredoc_ptrs[i], &fd[1], &input, file_loc);
		if (heredoc_mult_process(check_error, file_loc, fd) < 0)
			return (-1);
		implement_heredoc(&fd[1], input, fd[0]);
		close(fd[1]);
		close(fd[0]);
		frees_split(input);
		if (i < heredoc_count - 1 && *file_loc)
		{
			unlink(*file_loc);
			free(*file_loc);
			*file_loc = NULL;
		}
		i++;
	}
	return (0);
}

int	heredoc(char *temp, char **file_loc, size_t size)
{
	char	**heredoc_ptrs;
	char	*search;
	int		heredoc_count;
	int		fd[2];

	search = (temp);
	heredoc_count = 0;
	heredoc_ptrs = malloc((size + 1) * sizeof(char *));
	while (1)
	{
		search = ft_strnstr(search, "<<", ft_strlen(search));
		if (search == NULL)
			break ;
		heredoc_ptrs[heredoc_count++] = search;
		search += 2;
	}
	heredoc_ptrs[heredoc_count] = NULL;
	if (heredoc_mult(heredoc_count, file_loc, heredoc_ptrs) < 0)
	{
		free(heredoc_ptrs);
		return (-1);
	}
	free(heredoc_ptrs);
	return (0);
}
