/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:06:12 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/25 18:10:08 by nqasem           ###   ########.fr       */
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
	while (ft_isspace(temp[i]))
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

int	ft_heredoc_redirection_manager_2(int *j, char **str, char **tmp)
{
	char	*tmp2;

	if ((*tmp) && ((*tmp)[1] != '<') && ((*tmp)[0] == '<' || (*tmp)[0] == '>'))
	{
		if ((*tmp)[1] == '>')
		{
			(*tmp)[1] = ' ';
			*j = 1;
		}
		if (ft_heredoc_redirection_process(str, (*tmp)))
			return (-1);
		tmp2 = ft_strmchr((*tmp) + 1, "<>");
		(*tmp) = tmp2;
	}
	else
	{
		tmp2 = ft_strmchr((*tmp) + 2, "<>");
		(*tmp) = tmp2;
	}
	return (0);
}

int	execute_heredoc_setup_exe(char *file, t_cmd **cmd, int i, char **temp)
{
	int	fd;

	if (!((*cmd)->here_doc->file_loc)[i])
	{
		ft_printf("%2Error: file_loc[%d] is NULL in execute_heredoc\n", i);
		return (-1);
	}
	fd = open(((*cmd)->here_doc->file_loc)[i], O_RDONLY);
	handle_here_doc_nolink(cmd);
	if (fd < 0)
	{
		ft_printf("%2open heredoc file\n");
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

int	execute_heredoc_manage_exeu(char *file, char **str, t_cmd **cmd, char *temp)
{
	if (ft_heredoc_redirection_manager(file, str) < 0)
	{
		free(temp);
		free((*str));
		return (-1);
	}
	if (!(*str))
	{
		if (ft_execve(temp, (*cmd)->env))
		{
			ft_printf("%2Command not found\n");
			(*cmd)->exit_status = 127;
			if (temp)
				free(temp);
			return (-1);
		}
	}
	return (0);
}

int	execute_heredoc_redirection(char ***redirection_split, char *str, char *st,
		t_cmd **cmd)
{
	if (ft_redirection(st, redirection_split, cmd) < 0)
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
