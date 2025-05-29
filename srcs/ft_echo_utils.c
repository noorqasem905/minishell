/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:47:06 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/29 15:05:36 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_setquotes(int *quotes, int *first, int value)
{
	*first = value;
	quotes++;
}

int	ft_echo_quotes(char *word, int *igonre)
{
	int	double_quotes;
	int	single_quotes;
	int	first;
	int	i;

	single_quotes = 0;
	double_quotes = 0;
	first = 0;
	i = -1;
	while (word[++i])
	{
		if ((*igonre) == 0)
			(*igonre) = first;
		if (word[i] == '\'' && first == 0)
			ft_echo_setquotes(&single_quotes, &first, 1);
		else if (word[i] == '\"' && first == 0)
			ft_echo_setquotes(&double_quotes, &first, 2);
		else if (word[i] == '\'' && first == 1)
			ft_echo_setquotes(&single_quotes, &first, 0);
		else if (word[i] == '\"' && first == 2)
			ft_echo_setquotes(&double_quotes, &first, 0);
	}
	if (first != 0)
		return (-1);
	return (0);
}

int	ft_echo_quotes_manger(char **split, int *i, int *ignore, char **buff)
{
	char	*tmp;

	while (split[(*i)] && split[++(*i)])
	{
		if (ft_echo_quotes(split[(*i)], ignore) < 0)
		{
			if (*buff)
				free(*buff);
			frees_split(split);
			return (-1);
		}
		tmp = ft_strjoin(*buff, " ");
		free(*buff);
		(*buff) = tmp;
		tmp = ft_strjoin(*buff, split[(*i)]);
		free(*buff);
		(*buff) = tmp;
	}
	frees_split(split);
	return (0);
}

void	ft_echo_ignore_quotes(int new_line, int ignore, char *buff)
{
	char	quote;
	char	*src;
	char	*dst;

	if (!buff)
	{
		printf("%c", new_line);
		return ;
	}
	quote = 0;
	if (ignore == 1)
		quote = '\'';
	else if (ignore == 2)
		quote = '\"';
	src = buff;
	dst = buff;
	while (*src)
	{
		if (*src != quote)
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
	printf("%s%c", buff, new_line);
	free(buff);
}

char	*strip_outer_quotes(char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if ((str[0] == '\'' || str[0] == '\"') && str[len - 1] == str[0] && len > 1)
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}
