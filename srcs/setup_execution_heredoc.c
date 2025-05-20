/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_execution_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:11:43 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/20 19:15:43 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	 counter_total_heredoc(t_here_doc **here_doc, char *str)
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

int	searching_here_doc_2(t_cmd **cmd, t_here_doc **here_doc, t_list **current,
		int i_p[])
{
	int		check_error;
	char	*temp;

	if (ft_strfind((*current)->content, "<<"))
	{
		(*cmd)->who_am_i = 13;
		counter_total_heredoc(here_doc, (*current)->content);
		temp = ft_strnstr((*current)->content, "<<",
				ft_strlen((*current)->content));
		check_error = handle_here_doc(temp);
		if (check_error < 0)
		{
			printf("error here doc\n");
			(*cmd)->exit_status = -14;
			return (-1);
		}
		(*here_doc)->pryority[i_p[0]] = 2 + i_p[1];
		(*here_doc)->counter++;
		i_p[1]++;
	}
	else
		(*here_doc)->pryority[i_p[0]] = 1;
	(*current) = (*current)->next;
	return (0);
}

int	searching_here_doc(t_cmd **cmd, t_here_doc **here_doc)
{
	t_list	*current;
	int		i_p[2];

	i_p[0] = 0;
	i_p[1] = 0;
	current = (*cmd)->word;
	(*here_doc)->counter = 0;
	(*here_doc)->counter_total = 0;
	while (current != NULL)
	{
		if (searching_here_doc_2(cmd, here_doc, &current, i_p) < 0)
			return (-1);
		i_p[0]++;
	}
	(*here_doc)->pryority[i_p[0]] = '\0';
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

int	setup_execution(t_cmd **cmd, int *size)
{
	(*size) = ft_lstsize((*cmd)->word);
	(*cmd)->here_doc->pryority = NULL;
	if (*size > 300)
		return (65);
	(*cmd)->here_doc->pryority = malloc(sizeof(int) * (*size + 1));
	(*cmd)->here_doc->pryority[*size] = '\0';
	(*cmd)->who_am_i = 0;
	(*cmd)->here_doc->index = 0;
	if (searching_here_doc(cmd, &(*cmd)->here_doc) == -1)
	{
		perror("Error in here doc");
		return (-13);
	}
	return (0);
}
