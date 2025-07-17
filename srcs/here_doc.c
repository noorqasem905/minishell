/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:48:10 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/17 11:41:02 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	here_doc_manger(t_cmd **cmd, char **file_loc)
{
	t_list	*current;
	int		size;
	int		i_j[2];

	i_j[0] = 0;
	i_j[1] = 0;
	current = (*cmd)->word;
	while ((*cmd)->here_doc->pryority[i_j[0]] != '\0')
	{
		if ((*cmd)->here_doc->pryority[i_j[0]] >= 2)
		{
			size = sizeof_heredoc(current->content);
			if (size > 1023 || heredoc(current->content, &(file_loc[i_j[1]]),
					size, cmd) < 0)
			{
				ft_printf("%2heredoc initialize\n");
				return (-1);
			}
			i_j[1]++;
		}
		current = current->next;
		i_j[0]++;
	}
	return (0);
}

int	implement_heredoc(int *fd, char **input, int original_stdout, t_cmd **cmd)
{
	char	*here_doc;

	g_exit_status = 0;
	while (1)
	{
		here_doc = readline(">");
		if (!here_doc || handle_exit_heredoc(here_doc)
			|| ft_strcmp(here_doc, input[0]) == 0)
		{
			free(here_doc);
			break ;
		}
		write_and_expand_line(fd, here_doc, original_stdout, cmd);
	}
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

int	heredoc_mult(int heredoc_count, char **file_loc, char *heredoc_ptrs[],
		t_cmd **cmd)
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
		implement_heredoc(&fd[1], input, fd[0], cmd);
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

int	heredoc(char *temp, char **file_loc, size_t size, t_cmd **cmd)
{
	char	**heredoc_ptrs;
	char	*search;
	int		heredoc_count;

	search = (temp);
	heredoc_count = 0;
	signal_handler_heredoc();
	heredoc_ptrs = malloc((size + 1) * sizeof(char *));
	if (!heredoc_ptrs)
		return (-1);
	while (1)
	{
		search = ft_strnstr(search, "<<", ft_strlen(search));
		if (search == NULL)
			break ;
		heredoc_ptrs[heredoc_count++] = search;
		search += 2;
	}
	heredoc_ptrs[heredoc_count] = NULL;
	if (heredoc_mult(heredoc_count, file_loc, heredoc_ptrs, cmd) < 0)
		return (free_err_ret(NULL, heredoc_ptrs, NULL, -1));
	free(heredoc_ptrs);
	signal(SIGINT, ssignal_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
