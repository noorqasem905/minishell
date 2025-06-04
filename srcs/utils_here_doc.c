/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:45:53 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/05 00:03:15 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_there_else_heredoc(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		while (temp[i] == '<' || temp[i] == '>')
			i++;
		while (isspace(temp[i]))
			i++;
		if (temp[i] == '\0' || temp[i] == '<' || temp[i] == '>')
			return (-8);
		while (temp[i] != '\0' && temp[i] != '<' && temp[i] != '>'
			&& !isspace(temp[i]))
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

	i = 2;
	err_after = -3;
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
	if (get_free_filename(file_loc, "/tmp/minishell_heredoc") < 0)
	{
		ft_printf("%2malloc invalid\n");
		return (-1);
	}
	*fd = open(*file_loc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
	{
		ft_printf("%2open\n");
		free(*file_loc);
		return (-1);
	}
	return (*fd);
}
