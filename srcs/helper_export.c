/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:09:09 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/01 01:24:16 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_delimiters(const char **s, char c)
{
	while (**s == c && **s)
		(*s)++;
}

void	skip_word(char const **s, char c, int *flag, char *quote_char)
{
	while (**s && (**s != c || *flag))
	{
		if (*flag && **s == *quote_char)
			*flag = 0;
		else if (!*flag && (**s == '\'' || **s == '"'))
		{
			*flag = 1;
			*quote_char = **s;
		}
		(*s)++;
	}
}

static void	init_variable(int *flag, size_t *i, char *quote_char)
{
	*i = 0;
	*flag = 0;
	*quote_char = 0;
}

int	split_loop(char **str, const char *s, char c, size_t *i, char *quote_char)
{
	int		flag;
	size_t	word_len;

	flag = 0;
	while (*s)
	{
		skip_delimiters(&s, c);
		if (*s)
		{
			word_len = word_len_custom((char *)s, c, &flag, quote_char);
			str[*i] = ft_substr(s, 0, word_len);
			if (!str[*i])
			{
				free_it(str, *i);
				return (0);
			}
			(*i)++;
			s += word_len;
		}
	}
	return (1);
}

char	**ft_split_custom_exp(const char *s, char c)
{
	char	quote_char;
	char	**str;
	int		flag;
	size_t	i;

	if (!s)
		return (NULL);
	init_variable(&flag, &i, &quote_char);
	str = malloc(sizeof(char *) * (word_count_custom(s, c) + 1));
	if (!str)
		return (NULL);
	if (!split_loop(str, s, c, &i, &quote_char))
		return (NULL);
	str[i] = NULL;
	return (str);
}

