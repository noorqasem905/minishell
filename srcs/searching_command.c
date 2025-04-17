/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:12:14 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/17 19:24:38 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    searching_comand(char **input, char **temp)
{
    if (ft_strcmp(temp[0], "exit") == 0)
	{
		// free(*input);
        return (-1);
    }
    // if (ft_strcmp(temp[0], "clear") == 0) {
    //     // clear_terminal(); // Clear the terminal
    //     clear_history();
    //     // free(*input);
    //     return (0);
    // }
    return (0);
}