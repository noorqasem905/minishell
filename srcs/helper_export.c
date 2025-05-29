/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:09:09 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/29 15:01:38 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_quotes(char **s, int *flag, char *quote_char)
{
    if (**s == '\'' || **s == '\"')
    {
        *quote_char = **s;
        *flag = !(*flag);
        (*s)++;
        return (1);
    }
    return (0);
}

void	skip_delimiters(char **s, char c, int *flag, char *quote_char)
{
    while (**s == c && **s)
    {
        if (handle_quotes(s, flag, quote_char))
            continue ;
        (*s)++;
    }
}

void	skip_word(char **s, char c, int *flag, char *quote_char)
{
    while (**s && (**s != c || *flag == 1))
    {
        if (*flag && **s == *quote_char)
        {
            *flag = 0;
            (*s)++;
            continue ;
        }
        if (handle_quotes(s, flag, quote_char))
            continue ;
        (*s)++;
    }
}

static void	init_varaible(int *flag, size_t *i, char *quote_char)
{
	*i = 0;
    *flag = 0;
    *quote_char = 0;
}

char	**ft_split_custom_exp(char const *s, char c)
{
    char	quote_char;
    char	**str;
    int		flag;
    size_t	i;

	init_varaible(&flag, &i, &quote_char);
    str = malloc(sizeof(char *) * (word_count_custom(s, c) + 1));
    if (!s || !str)
        return (NULL);
    while (*s)
    {
        skip_delimiters((char **)&s, c, &flag, &quote_char);
        if (*s)
        {
            str[i] = ft_substr(s, 0, word_len_custuom((char *)s, c, &flag, &quote_char));
            if (!str[i++])
            {
                free_it(str, i - 1);
                return (NULL);
            }
            s += word_len_custuom((char *)s, c, &flag, &quote_char);
        }
    }
    str[i] = NULL;
    return (str);
}

