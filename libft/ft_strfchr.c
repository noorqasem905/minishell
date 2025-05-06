/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:57:04 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/06 21:48:35 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include <string.h>

char	*ft_strfchr(const char *s, int c)
{
	char	cca;
	char	*temp;
	char	*copy;

	cca = (char)c;
	copy = strdup(s);
	if (!copy)
		return (NULL);
	temp = copy;
	while (*temp != '\0' && *temp != cca)
	{
		temp++;
	}
	if (*temp != '\0' && *temp == cca)
	{
		*temp = '\0';
		return (copy);
	}
	free(copy);
	return (NULL);
}

/* #include <stdio.h>
int	main(void)
{
    char *inter = "ls here_doc.c < f< c< test.txt>d";
	//char	j[] = "abc";
	// char	k[] = "abcdcl";

	printf("THE VALUE IS: %s", ft_strfchr(inter, '<'));
	//printf("THE VALUE IS: %s", strchr(k, 'd'));
	//      printf("THE VALUE IS: %d \n",++d);
}
 */