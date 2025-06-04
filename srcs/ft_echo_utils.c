/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:47:06 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/04 21:57:49 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_setquotes(char *first, char value)
{
	*first = value;
}

int	ft_echo_quotes(char *word, char *ignore)
{
	size_t	len;

	*ignore = '\0';
	len = ft_strlen(word);
	if (len >= 2 && (word[0] == '\'' || word[0] == '\"') && word[0] == word[len
			- 1])
	{
		*ignore = word[0];
	}
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
