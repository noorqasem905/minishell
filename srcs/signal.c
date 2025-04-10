/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:56:26 by aalquraa          #+#    #+#             */
/*   Updated: 2025/04/10 18:16:10 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int signal_handler(int x)
{
    (void)x;
    
    ft_printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
