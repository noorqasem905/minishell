/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:48:10 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/26 21:27:55 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printf_split(char *str, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("%2%s%s\n",str, split[i]);
		i++;
	}
}

int	here_doc(void)
{
    char    **input;
    char	*temp;
    int     fd;
    int     check;
    int     i;

    i = 0;
    check = 0;
    temp = ft_strmchr("ls << exit", "<<");
    ftstrcmp(temp, "<<");
    input = ft_mult_split(temp, "<<");
    printf_split("here doc: ", input);
    // check = 
    return (0);
}

int main(void)
{
    char    **input;
    char	*temp;
    int     fd;
    int     check;
    int     i;

    i = 0;
    check = 0;
    temp = ft_strmchr("ls << exit", "<<");
    input = ft_mult_split(temp, "<<");
    printf_split("here doc", input);
}
/*
here doc

formula << exit
> ls
> ls -l
> ls -a
> exit
RoboShell>

step 1: find the here doc formula
step 2: find the exit if no error and no here doc
step 3: find the here doc are correct
step 4: do the here doc
*/