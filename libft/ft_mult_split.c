/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:28:06 by nqasem            #+#             */
/*   Updated: 2025/04/22 22:08:36 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	frees_mult_split(char **root)
{
	int	i;

	i = 0;
	while (root[i])
	{
		free(root[i]);
		i++;
	}
	free(root);
	root = NULL;
}

char	*find_break_char(char const *s, char c[], int size)
{
	int	j;

	while (*s)
	{
		j = 0;
		while (j < size)
		{
			if (*s == c[j])
				return ((char *)s);
			j++;
		}
		s++;
	}
	return ((char *)s);
}

static int	word_mult_count(char const *s, char c[])
{
	int	i;
	int	size;
	int	j;

	i = 0;
	size = ft_strlen(c);
	while (*s)
	{
		j = 0;
		while (j < size && *s)
		{
			if (*s == c[j])
			{
				s++;
				j = 0;
			}
			else
				j++;
		}
		if (*s)
			i++;
		s = find_break_char(s, c, size);
	}
	return (i);
}

static void	free_mult_it(char **str, size_t i)
{
	while (i != 0)
	{
		free(str[i]);
		i--;
	}
	free(str[i]);
	free(str);
}

static size_t	word_mult_len(char *s, char c[])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (c[j])
		{
			if (s[i] == c[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

char	*skip_delimiter(char *s, char c[], size_t size)
{
	int	j;

	j = 0;
	while (j < size && *s)
	{
		if (*s == c[j])
		{
			s++;
			j = 0;
		}
		else
			j++;
	}
	return (s);
}

char	*setup_data(char *s, char c[], char **str, size_t *i)
{
	if (*s)
	{
		str[*i] = ft_substr(s, 0, word_mult_len((char *)s, c));
		if (!str[*i])
		{
			free_mult_it(str, *i);
			return (NULL);
		}
		s += word_mult_len((char *)s, c);
		(*i)++;
	}
	return (s);
}

char	**ft_mult_split(char const *s, char c[])
{
	char	**str;
	size_t	i;
	size_t	size;
	int		words;

	if (!s)
		return (NULL);
	i = 0;
	size = ft_strlen(c);
	words = word_mult_count(s, c);
	str = malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	while (*s)
	{
		s = skip_delimiter((char *)s, c, size);
		s = setup_data((char *)s, c, str, &i);
		if (!s)
			return (NULL);
	}
	str[i] = NULL;
	return (str);
}
/*
int	main(void)
{
	char *str = "123456789 wor,ld, this is a test";
	char delimiter[] = {'w', '\0'};
	char **result;
	int i = 0;

	result = ft_mult_split(str, delimiter);
	while (result && result[i])
	{
		printf("Word %d: %s\n", i, result[i]);
		i++;
	}
	if (result)
		frees_mult_split(result);
	return (0);
} */
