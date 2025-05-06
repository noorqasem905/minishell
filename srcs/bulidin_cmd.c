/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulidin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:12:14 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/06 15:51:36 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		handle_cd_slash(char *temp)
{
	if (temp == NULL)
	{
		chdir(getenv("HOME"));
		return (-1);
	}
	if (temp[0] == '/')
	{
		if (chdir(temp) == -1)
		{
			perror("cd");
			return (-1);
		}
		return (-1);
	}
	return (0);
}

int		handle_cd_dup_dot(char *temp)
{
	char	*parent;
	char	*cwd;

	if (ft_strcmp(temp, "..") == 0)
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
		{
			perror("getcwd");
			return (-1);
		}
		parent = ft_strrchr(cwd, '/');
		if (parent != NULL)
			*parent = '\0';
		if (chdir(cwd) == -1)
		{
			perror("cd");
			free(cwd);
			return (-1);
		}
		free(cwd);
		return (-1);
	}
	return (0);
}

int		build_quoted_string(char **dir, char ***temp, int total_len, int *end)
{
    char		quote;
    size_t		len;
	int			k;

	quote = (*temp)[1][0];
	*dir = malloc(total_len);
	if (!*dir)
	{
		perror("malloc");
		return (-1);
	}
	(*dir)[0] = '\0';
	k = 1;
	while (k <= (*end))
	{
		ft_strlcat(*dir, (*temp)[k], total_len);
		if (k != (*end))
			ft_strlcat(*dir, " ", total_len);
		k++;
	}
	if ((*dir)[0] == quote)
		ft_memmove(*dir, *dir + 1, ft_strlen(*dir));
	len = ft_strlen(*dir);
	if (len > 0 && (*dir)[len - 1] == quote)
		(*dir)[len - 1] = '\0';
	return (0);
}

int		merge_quoted_tokens(char ***temp, char **dir, int start, int *end)
{
    size_t		total_len;
    size_t		len;
    char		quote;
    int			k;

	quote = (*temp)[1][0];
	while ((*temp)[(*end)] && (*temp)[(*end)][ft_strlen((*temp)[(*end)]) - 1] != quote)
		(*end)++;
	if ((*temp)[(*end)])
	{
		total_len = 0;
		k = start;
		while (k <= (*end))
		{
			total_len += ft_strlen((*temp)[k]) + 1;
			k++;
		}
		if (build_quoted_string(dir, temp, total_len, end) == -1)
			return (-1);
	}
	return (0);
}

int		handle_space_infile(char ***temp, char **dir)
{
    size_t		total_len;
    size_t		len;
    char		quote;
    int			start;
    int			end;
    int			k;

	*dir = NULL;
    if ((*temp)[1] && ((*temp)[1][0] == '"' || (*temp)[1][0] == '\''))
    {
        quote = (*temp)[1][0];
        start = 1;
        end = start;
		if(merge_quoted_tokens(temp, dir, start, &end))
			return (-1);
    }
    else if ((*temp)[1])
        *dir = (*temp)[1];
    else
        *dir = NULL;
    return (0);
}

int		robo_cd_access(char **dir, char **temp)
{
	if ((*dir) && access((*dir), F_OK) == 0)
    {
        if (chdir((*dir)) == -1)
        {
			write(1,"No file named this\n" ,20);
            if ((*dir) != temp[1])
                free((*dir));
            return (-1);
        }
        if ((*dir) != temp[1])
		{
			write(1,"No file named this\n" ,20);
            free((*dir));
		}
		return (-1);
    }
	else
		write(1,"No file named this\n" ,20);
	return (0);
}

void	robo_cd(char **temp, char **robo_env)
{
    char	*dir;

    if(handle_cd_slash(temp[1]) == -1)
        return ;
    if(handle_cd_dup_dot(temp[1]) == -1)
        return ;
    if(handle_space_infile(&temp, &dir) == -1)
        return ;
	if(robo_cd_access(&dir, temp))
		return ;
    if (dir != temp[1] && dir != NULL)
	{
		write(1,"No file named this\n" ,20);
		free(dir);
	}
	if (chdir(temp[1]) == -1)
    return ;
}

int	searching_comand(char **input, char **temp)
{
	if (ft_strcmp(temp[0], "exit") == 0)
		return (-13);
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
