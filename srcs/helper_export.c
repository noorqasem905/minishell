/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:00:34 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/15 17:58:26 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	word_count(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

int	word_count_custuom(char const *s, char c)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (*s)
	{
		while (*s == c && *s && *s != '\"')
		{
			if (*s == '\"')
			{
				flag = 1;
				s++;
			}
			s++;
		}
		if (*s)
			i++;
		while (*s && (*s != c || flag == 1))
		{
			if (*s == '\"')
			{
				flag = 0;
			}
			s++;
		}
	}
	return (i);
}
size_t	word_len_custuom(char *s, char c, int *flag)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] != c || *flag))
	{
		if (s[i] == '\"')
		{
			*flag = !(*flag);
			i++;
			continue ;
		}
		i++;
	}
	return (i);
}

char	**ft_split_custom_exp(char const *s, char c)
{
	char **str;
	size_t i;
	int flag = 0;

	i = 0;
	str = malloc(sizeof(char *) * (word_count_custuom(s, c) + 1));
	if (!s || !str)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			str[i] = ft_substr(s, 0, word_len_custuom((char *)s, c, &flag));
			if (!str[i++])
			{
				free_it(str, i - 1);
				return (NULL);
			}
			s += word_len_custuom((char *)s, c, &flag);
		}
	}
	str[i] = NULL;
	return (str);
}