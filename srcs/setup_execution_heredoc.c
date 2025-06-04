/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_execution_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:11:43 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/05 00:22:36 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	counter_total_heredoc(t_here_doc **here_doc, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && '<' == str[i + 1])
			(*here_doc)->counter_total++;
		i++;
	}
}

int	handle_here_doc_qouts(char *temp)
{
	int		i;
	int		flag;
	int		enter;
	char	quote_char;

	i = -1;
	flag = 0;
	enter = 1;
	while (temp[++i])
	{
		if (temp[i] == '"' || temp[i] == '\'')
		{
			enter = 0;
			if (flag == 0)
			{
				flag = 1;
				quote_char = temp[i];
			}
			else if (flag == 1 && temp[i] == quote_char)
				flag = 0;
		}
	}
	if (enter == 1)
		return (1);
	return (flag);
}

int	searching_here_doc_2_logic(
	t_cmd **cmd, t_here_doc **here_doc,
	t_list **current, int i_p[])
{
	char	*temp;
	int		check_error;

	(*cmd)->exit_status = 2;
	(*cmd)->who_am_i = 13;
	counter_total_heredoc(here_doc, (*current)->content);
	temp = ft_strnstr(
			(*current)->content, "<<", ft_strlen((*current)->content));
	check_error = handle_here_doc(temp);
	if (check_error < 0)
	{
		(*cmd)->exit_status = -14;
		return (-1);
	}
	(*here_doc)->pryority[i_p[0]] = 2 + i_p[1];
	(*here_doc)->counter++;
	i_p[1]++;
	if (check_extra_redirection((*current)->content) < 0)
		return (-1);
	return (0);
}

int	sizeof_heredoc(char *str)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '<' && str[i + 1] == '<')
		{
			size++;
			i++;
		}
		i++;
	}
	return (size);
}

int	setup_execution(t_cmd **cmd)
{
	int		size;

	(size) = ft_lstsize((*cmd)->word);
	(*cmd)->here_doc->pryority = NULL;
	if (size > 300)
		return (65);
	(*cmd)->here_doc->pryority = malloc(sizeof(int) * (size + 1));
	if (!(*cmd)->here_doc->pryority)
		return (-1);
	(*cmd)->here_doc->pryority[size] = '\0';
	(*cmd)->who_am_i = 0;
	(*cmd)->here_doc->index = 0;
	if (searching_here_doc(cmd, &(*cmd)->here_doc) == -1)
	{
		ft_printf("%2syntax error near unexpected token `newline`\n");
		(*cmd)->exit_status = 2;
		return (-13);
	}
	return (0);
}
