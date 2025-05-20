/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:06:12 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/20 17:40:02 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_heredoc_redirection_process(char **str, char *temp)
{
	char	*st;
	char	*tmp;
	char	*tmp2;
	int		ret;
	int		i;

	i = 1;
	while (isspace(temp[i]))
		i++;
	if (temp[i] == '\0' || temp[i] == '<' || temp[i] == '>')
		return (-1);
	st = ft_strmfchr(temp + i, " <>");
	ret = which_redirection_char(temp);
	if (ret == '<')
		tmp = ft_strjoin("<", st);
	else
		tmp = ft_strjoin(">", st);
	free(st);
	st = tmp;
	tmp2 = ft_strjoin(*str, st);
	free(st);
	free(*str);
	*str = tmp2;
	return (0);
}

int	ft_heredoc_redirection_manager(char *file, char **str)
{
	char	*tmp2;
	char	*tmp;
	char	*st;

	*str = NULL;
	tmp = ft_strmchr(file, "<>");
	while (tmp != NULL)
	{
		if (tmp && tmp[1] != '<' && (tmp[0] == '<' || tmp[0] == '>'))
		{
			ft_heredoc_redirection_process(str, tmp);
			tmp2 = ft_strmchr(tmp + 1, "<>");
			tmp = tmp2;
		}
		else
		{
			tmp2 = ft_strmchr(tmp + 2, "<>");
			tmp = tmp2;
		}
	}
	return (0);
}

int	execute_heredoc_setup_exe(char *file, char **file_loc, int i, char **temp)
{
	int	fd;

	if (!file_loc[i])
	{
		dprintf(2, "Error: file_loc[%d] is NULL in execute_heredoc\n", i);
		return (-1);
	}
	fd = open(file_loc[i], O_RDONLY);
	free(file_loc[i]);
	if (fd < 0)
	{
		perror("open heredoc file");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	if (manager_execution_heredoc(file, temp) < 0)
	{
		free(*temp);
		return (-1);
	}
	close(fd);
	return (0);
}

int	execute_heredoc_manage_exeu(char *file, char **str, char **ev, char *temp)
{
	if (ft_heredoc_redirection_manager(file, str) < 0)
	{
		free(temp);
		free((*str));
		return (-1);
	}
	if (!(*str))
	{
		if (ft_execve(temp, ev))
		{
			if (temp)
				free(temp);
			return (-1);
		}
	}
	return (0);
}

int	execute_heredoc_redirection(char ***redirection_split, char *str, char *st,
		char **ev)
{
	if (ft_redirection(st, redirection_split, ev) < 0)
	{
		if (str)
			free(str);
		if (st)
			free(st);
		return (-1);
	}
	if (str)
		free(str);
	if (st)
		free(st);
	return (0);
}
