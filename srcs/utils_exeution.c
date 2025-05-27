/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exeution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:08:07 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/27 16:01:39 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_init(t_cmd **cmd, int size)
{
	int	i;

	i = 0;
	(*cmd)->pryority = malloc(sizeof(int) * (size + 1));
	if ((*cmd)->pryority == NULL)
	{
		perror("malloc");
		return (-1);
	}
	while (i < size)
	{
		(*cmd)->pryority[i] = 0;
		i++;
	}
	(*cmd)->pryority[i] = -1;
	return (0);
}

int	ft_strfind(char *str, char *c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == c[0])
		{
			j = 0;
			while (str[i + j] && str[i + j] == c[j])
				j++;
			if (c[j] == '\0' && ft_strlen(c) == j)
				return (1);
		}
		i++;
	}
	return (0);
}

int	str_size_element(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

void	setup_extra_command_h_2(char **split_2, char **command)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 1;
	tmp = ft_strjoin(*command, " ");
	if (!tmp)
		return ;
	free(*command);
	*command = tmp;
	while (j < (int)element_size(split_2))
	{
		tmp = ft_strjoin(split_2[j], " ");
		if (tmp)
		{
			tmp2 = ft_strjoin(*command, tmp);
			free(tmp);
			free(*command);
			*command = tmp2;
		}
		j++;
	}
}

int	setup_extra_command_h(char *temp5, char **command)
{
	char	**split;
	char	**split_2;
	int		i;

	split = ft_mult_split(temp5, "<>");
	if (!split)
		return (-13);
	i = 0;
	while (i < (int)element_size(split))
	{
		split_2 = ft_split(split[i], ' ');
		if (!split_2)
		{
			frees_split(split);
			return (-13);
		}
		setup_extra_command_h_2(split_2, command);
		frees_split(split_2);
		i++;
	}
	frees_split(split);
	return (0);
}

/* void	print_saved_cmd1(t_list *saved_cmd)
{
	t_list	*current;

	current = saved_cmd;
	while (current != NULL)
	{
		ft_printf("Command: %s\n", (char *)current->content);
		current = current->next;
	}
}


void	pprintf(char **str)
{
	int	no;

	no = 0;
	while (str[no])
	{
		dprintf(2,"out: %s\n", str[no]);
		no++;
	}
}

 */