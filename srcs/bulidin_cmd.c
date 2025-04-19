/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulidin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:12:14 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/19 18:40:06 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void robo_cd(char **temp, char **robo_env)
{
    if (temp[1] == NULL)
    {
        chdir(getenv("HOME"));
        return ;
    }
    if (temp[1][0] == '/')
    {
        if (chdir(temp[1]) == -1)
        {
            perror("cd");
            return ;
        }
        return ;
    }
    if (ft_strcmp(temp[1], "..") == 0)
    {
        char *cwd = getcwd(NULL, 0);
        if (cwd == NULL)
        {
            perror("getcwd");
            return ;
        }
        char *parent = ft_strrchr(cwd, '/');
        if (parent != NULL)
            *parent = '\0';
        if (chdir(cwd) == -1)
        {
            perror("cd");
            free(cwd);
            return ;
        }
        free(cwd);
        return ;
    }
        char *o = malloc(sizeof(char) * 100);
        // if (temp[1][0] == '"')
        {
            int k = 0;
            int i = 0;
            int j = 1;
            // o = ft_strchr(temp[1], '\"');
 /*             while (temp[i])
            {
                    dprintf(2,"temp[%i] = %s\n",i, temp[1]);
                while (temp[i][j] != '\"' && temp[i][j] != '\0')
                {
                    o[k] = temp[i][j];
                    dprintf(2,"temp[%i] = %c\n",j, temp[1][j]);
                    j++;
                    k++;
                }
                i++;
                j = 0;
            } */
            
        }
        dprintf(2,"o = %s\n", o);
    if (access(o, F_OK) == 0)
    {
        if (chdir(o) == -1)
        {
            perror("cd");
            return ;
        }
        return ;
    }
    if (chdir(temp[1]) == -1)
    {
        perror("cd");
        return ;
    }
}

int    searching_comand(char **input, char **temp)
{
    if (ft_strcmp(temp[0], "exit") == 0)
	{
		free(*input);
        return (-13);
    }
	if (!ft_strncmp(temp[0], "cd", 3))
		return (1);
	if (!ft_strncmp(temp[0], "export", 7))
		return (1);
	if (!ft_strncmp(temp[0], "unset", 6))
		return (1);
	if (!ft_strncmp(temp[0], "exit", 5))
		return (1);
	if (!ft_strncmp(temp[0], "env", 4))
		return (1);
	if (!ft_strncmp(temp[0], "pwd", 4))
		return (1);
	if (!ft_strncmp(temp[0], "echo", 5))
		return (1);
    return (0);
}
