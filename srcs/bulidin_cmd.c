/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulidin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:12:14 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/20 22:00:36 by nqasem           ###   ########.fr       */
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
    char *dir = NULL;
    if (temp[1] && (temp[1][0] == '"' || temp[1][0] == '\''))
    {
        char quote = temp[1][0];
        int start = 1;
        int end = start;
        while (temp[end] && temp[end][ft_strlen(temp[end]) - 1] != quote)
            end++;
        if (temp[end])
        {
            size_t total_len = 0;
            int k = start;
            while (k <= end)
            {
                total_len += ft_strlen(temp[k]) + 1;
                k++;
            }
            dir = malloc(total_len);
            if (!dir)
            {
                perror("malloc");
                return;
            }
            dir[0] = '\0';
            k = start;
            while (k <= end)
            {
                ft_strlcat(dir, temp[k], total_len);
                if (k != end)
                    ft_strlcat(dir, " ", total_len);
                k++;
            }
            if (dir[0] == quote)
                ft_memmove(dir, dir + 1, ft_strlen(dir));
            size_t len = ft_strlen(dir);
            if (len > 0 && dir[len - 1] == quote)
                dir[len - 1] = '\0';
        }
    }
    else
    {
        dir = temp[1];
    }
    if (dir && access(dir, F_OK) == 0)
    {
        if (chdir(dir) == -1)
        {
            perror("cd");
            if (temp[1] && temp[1][0] == '"')
                free(dir);
            return;
        }
        if (temp[1] && temp[1][0] == '"')
            free(dir);
        return;
    }
    if (temp[1] && temp[1][0] == '"')
        free(dir);
    if (chdir(temp[1]) == -1)
    {
        perror("cd");
        return;
    }
}

int    searching_comand(char **input, char **temp)
{
    if (ft_strcmp(temp[0], "exit") == 0)
	{
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
