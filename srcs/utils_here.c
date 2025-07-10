/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:07:30 by aalquraa          #+#    #+#             */
/*   Updated: 2025/07/10 14:08:08 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	{
		close(*fd);
		return (-1);
	}
	return (check_error);
}

int	handle_exit_heredoc(char *here_doc)
{
	if (g_exit_status == 130)
	{
		free(here_doc);
		return (1);
	}
	return (0);
}

void	write_and_expand_line(int *fd, char *here_doc,
			int original_stdout, t_cmd **cmd)
{
	t_list	str;
	char	*str_ntr;
	size_t	len;

	str.content = here_doc;
	str.next = NULL;
	str_ntr = expander_input(cmd, &str);
	if (str_ntr)
	{
		free(here_doc);
		here_doc = str_ntr;
	}
	len = ft_strlen(here_doc);
	dup2((*fd), STDOUT_FILENO);
	write(*fd, here_doc, len);
	write(*fd, "\n", 1);
	dup2(original_stdout, STDOUT_FILENO);
	free(here_doc);
}
