/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_custom_exp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:09:34 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/26 21:51:08 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_delimiters(char **s, char c, int *flag)
{
	while (**s == c && **s && **s != '\"')
	{
		if (handle_quotes(s, flag))
			continue ;
		(*s)++;
	}
}

static void	skip_word(char **s, char c, int *flag)
{
	while (**s && (**s != c || *flag == 1))
	{
		if (handle_quotes(s, flag))
			continue ;
		(*s)++;
	}
}

int	word_count_custom(char const *s, char c)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (*s)
	{
		skip_delimiters((char **)&s, c, &flag);
		if (*s)
			i++;
		skip_word((char **)&s, c, &flag);
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
	char	**str;
	size_t	i;
	int		flag;

	flag = 0;
	i = 0;
	str = malloc(sizeof(char *) * (word_count_custom(s, c) + 1));
	if (!s || !str)
		return (NULL);
	while (*s)
	{
		ski_delimiters((char **)&s, c);
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
