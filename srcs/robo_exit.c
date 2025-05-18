/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:29:22 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/14 19:21:24 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


int check_n(char *n)
{
    int i;
    
    i = 0;
    if (n[i] == '-' || n[i] == '+')
        i++;  
    while (n[i])
    {
        if (!ft_isdigit(n[i]))
            return (0);
        i++;
    }
    return (1);
}


void    robo_exit(char **str,t_cmd *cmd)

{
    int n;
    
    printf("Exiting\n");
    if (str[1])
    {
        if (!check_n(str[1]))
        {
            ft_printf("%2roboshell: exit: %s: numeric argument required", str[1]);
            cmd->exit_status = 255;
            free(cmd->word);
            free(cmd);
            exit(cmd->exit_status);
        }
        if (str[2])
        {
            ft_printf("%2robo: exit: too many arguments\n");
            cmd->exit_status = 1;
            return ;
        }
        n = ft_atoi(str[1]);
    }
    else
        n = cmd->exit_status;
        free_list(&cmd->word);
        free(cmd);
        exit((unsigned char)n);
}
