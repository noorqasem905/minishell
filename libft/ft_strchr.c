/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:03:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/05 01:30:15 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmchr(const char *s, char c[])
{
	int		i;

	while (*s != '\0')
	{
		i = 0;
		while (c[i] != '\0')
		{
			if (*s == c[i])
				return ((char *)s);
			i++;
		}
		s++;
	}
	return (NULL);
}

static void	is_quote(char c, int *in_quote, char *quote_char)
{
	*in_quote = 1;
	*quote_char = c;
}

char	*ft_strmchr_noqoute(const char *s, char c[])
{
    int		i;
    int		in_quote = 0;
    char	quote_char = 0;

    while (*s)
    {
        if ((*s == '"' || *s == '\''))
        {
            if (!in_quote)
				is_quote(*s, &in_quote, &quote_char);
            else if (*s == quote_char)
                in_quote = 0;
        }
        else if (!in_quote)
        {
            i = 0;
            while (c[i])
                if (*s == c[i++])
                    return ((char *)s);
        }
        s++;
    }
    return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	char	cca;

	cca = (char)c;
	while (*s != '\0' && *s != cca)
		s++;
	if (*s == cca)
		return ((char *)s);
	return (NULL);
}
/* 
#include <stdio.h>
int	main(void)
{
	char	j[] = "<>";
	char	k[] = "abc<dc>l";
	char	t[] = "abcdefg";
	char	*temp;

	temp = ft_strmchr(k, j); // i could set it as "<>" or "><"
	printf("THE VALUE IS: %s\n", temp); // output: <dc>l

	temp = ft_strmchr(temp + 1, j);
	printf("THE VALUE IS: %s\n", temp); // output: >l

	temp = ft_strmchr(temp + 1, j);
	printf("THE VALUE IS: %s\n", temp);// output: NULL

	printf("THE VALUE IS: %s", ft_strchr(t, 'd'));//output: defg 
}
 */