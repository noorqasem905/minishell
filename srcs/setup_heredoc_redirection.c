/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:08:08 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/27 22:08:35 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_heredoc_redirection_process_free(char *st, char **str)
{
	free(st);
	free(*str);
}

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
	if (!tmp)
		return (-1);
	st = tmp;
	tmp2 = ft_strjoin(*str, st);
	ft_heredoc_redirection_process_free(st, str);
	*str = tmp2;
	return (0);
}
