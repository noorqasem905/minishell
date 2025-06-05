/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:30:33 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/05 15:29:14 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	searching_here_doc_2(t_cmd **cmd, t_here_doc **here_doc, t_list **current,
		int i_p[])
{
	if (ft_strfind((*current)->content, "<<"))
	{
		if (searching_here_doc_2_logic(cmd, here_doc, current, i_p) < 0)
			return (-1);
	}
	else
		(*here_doc)->pryority[i_p[0]] = 1;
	(*current) = (*current)->next;
	return (0);
}
