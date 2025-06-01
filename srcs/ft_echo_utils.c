/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:47:06 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/01 14:47:23 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_setquotes(char *first, char value)
{
	*first = value;
}

int	ft_echo_quotes(char *word, char *ignore)
{
	char	first;
	int		i;

	first = '\0';
	i = -1;
	while (word[++i])
	{
		if (*ignore == '\0')
			*ignore = first;
		if (word[i] == '\'' && first == '\0')
			ft_echo_setquotes(&first, '\'');
		else if (word[i] == '\"' && first == '\0')
			ft_echo_setquotes(&first, '\"');
		else if (word[i] == '\'' && first == '\'')
			ft_echo_setquotes(&first, '\0');
		else if (word[i] == '\"' && first == '\"')
			ft_echo_setquotes(&first, '\0');
	}
	if (first != '\0')
		return (-1);
	return (0);
}

int	ft_echo_quotes_manger(char **split, int *index, char *ignore, char **buff)
{
	int	ret;

	*buff = ft_strdup("");
	if (!(*buff))
		return (-1);
	while (split[*index])
	{
		ret = process_token(buff, split[*index], ignore);
		if (ret < 0)
		{
			free(*buff);
			if (ret == -1)
				frees_split(split);
			return (-1);
		}
		(*index)++;
	}
	return (0);
}
