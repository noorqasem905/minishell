/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeute_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:40:16 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/22 20:09:02 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_filename(char **redirection_split, int ccount)
{
	char	*tmp;
	char	*filename;
	int		i;
	int		j;

	i = 0;
	j = -1;
	tmp = redirection_split[ccount];
	while (isspace(*tmp))
		tmp++;
	while (tmp[i] && !isspace(tmp[i]))
		i++;
	filename = malloc(i + 1);
	if (!filename)
		return (NULL);
	while (++j < i)
		filename[j] = tmp[j];
	filename[j] = '\0';
	return (filename);
}

int	ft_execute_redirection_p1(char **redirection_split, int ccount, int *fd)
{
	char	*tmp2;

	tmp2 = extract_filename(redirection_split, ccount);
	*fd = open(tmp2, O_RDONLY);
	free(tmp2);
	if (*fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(*fd);
		return (-1);
	}
	close(*fd);
	return (0);
}

int	ft_execute_redirection_p2(char **redirection_split, int ccount, int *fd)
{
	char	*tmp2;

	tmp2 = extract_filename(redirection_split, ccount);
	*fd = open(tmp2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(tmp2);
	if (*fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(*fd);
		return (-1);
	}
	close(*fd);
	return (0);
}

int	ft_execute_redirection_p3(char **redirection_split, int ccount, int *fd)
{
	char	*tmp2;

	tmp2 = extract_filename(redirection_split, ccount);
	*fd = open(tmp2, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(tmp2);
	if (*fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(*fd);
		return (-1);
	}
	close(*fd);
	return (0);
}

int	ft_execute_redirection(char **redirection_split, int ccount_i[], int *fd,
		char *temp3)
{
	if (ccount_i[1] == 6)
	{
		if (ft_execute_redirection_p3(redirection_split, ccount_i[0], fd) < 0)
			return (-1);
	}
	else if (temp3[0] == '<')
	{
		if (ft_execute_redirection_p1(redirection_split, ccount_i[0], fd) < 0)
			return (-1);
	}
	else if (temp3[0] == '>')
	{
		if (ft_execute_redirection_p2(redirection_split, ccount_i[0], fd) < 0)
			return (-1);
	}
	else
	{
		dprintf(2, "Error: Invalid redirection\n");
		return (-1);
	}
	return (0);
}
