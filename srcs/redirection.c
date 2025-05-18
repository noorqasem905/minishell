/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:00:09 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/17 07:01:50 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		init_check_redirection_mult(int mult[], int conflect_handle[], int is_file_enter[], int *i)
{
	int iter;

	*i = 0;
	iter = 0;
	while (iter < 2)
	{
		mult[iter] = 0;
		conflect_handle[iter] = 0;
		is_file_enter[iter] = 0;
		iter++;
	}
}

int	check_redirection_mult(char *input)
{
	int	mult;
	int	mult_2;
	int	i;
	int	handle;
	int	conflect;
	int	is_enter;
	int	is_file;

	mult = 0;
	mult_2 = 0;
	i = 0;
	handle = 0;
	conflect = 0;
	is_enter = 0;
	is_file = 0;
	// init_check_redirection_mult(mult, conflect_handle, int is_file_enter, &i)
	while (input[i])
	{
		if (input[i] == '<')
		{
			mult++;
			conflect++;
			if (is_enter > 0 && is_file == 0)
				return (-1);
			is_enter = 1;
			is_file = 0;
			if (input[i + 1] == '<' && handle == 0)
			{
				i++;
				handle = 1;
			}
			if (input[i + 1] == '>')
				return (-1);
		}
		else if (input[i] == '>')
		{
			mult_2++;
			conflect++;
			if (is_enter > 0 && is_file == 0)
				return (-1);
			is_enter = 2;
			is_file = 0;
			if (input[i + 1] == '>' && handle == 0)
			{
				i++;
				handle = 1;
			}
			if (input[i + 1] == '<')
				return (-1);
		}
		else if (input[i] != ' ' && input[i] != '>' && input[i] != '<')
		{
			conflect = 0;
			mult_2 = 0;
			mult = 0;
			is_enter = 0;
			is_file = 1;
		}
		if (mult > 1 || mult_2 > 1 || conflect > 1)
			return (-1);
		i++;
	}
	if (is_enter > 0 && is_file == 0)
		return (-1);
	if (mult > 1 || mult_2 > 1 || conflect > 1)
		return (-1);
	return (0);
}

int	setup_redirection(char *input, char **temp, char **temp2)
{
	char	state;
	int		mult;

	mult = check_redirection_mult(input);
	if (mult == -1)
	{
		dprintf(2, "Error: Multiple redirections\n");
		return (-1);
	}
	state = ft_strmchr(input, "<>")[0];
	if (state == '<')
	{
		*temp = ft_strfchr(input, '<');
		*temp2 = ft_strchr(input, '<');
	}
	else
	{
		*temp = ft_strfchr(input, '>');
		*temp2 = ft_strchr(input, '>');
	}
	return (0);
}

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

int	ft_execute_redirection(char **redirection_split, int ccount, int *fd,
		char *temp3, char **robo_env)
{
	if (temp3[0] == '<')
	{
		if (ft_execute_redirection_p1(redirection_split, ccount, fd) < 0)
			return (-1);
	}
	else if (temp3[0] == '>')
	{
		if (ft_execute_redirection_p2(redirection_split, ccount, fd) < 0)
			return (-1);
	}
	else
	{
		dprintf(2, "Error: Invalid redirection\n");
		return (-1);
	}
	return (0);
}

size_t	element_size(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	handle_mult_redirection(char *temp3, char *temp2, char **temp,
		char ***redirection_split)
{
	char	*tmp;
	int		p;
	int		px;

	if (!temp3)
	{
		tmp = ft_strrmchr(temp2, "<>");
		p = word_mult_count((tmp + 1), " <>");
		px = word_mult_count((temp2), " <>");
		// printf_split("OUT: ", *redirection_split);
		if ((element_size((*redirection_split)) == 2 || p == 2) && !*temp)
		{
			*temp = ft_strdup((*redirection_split)[px - 1]);
			return (5);
		}
		if (*temp != NULL)
			free(*temp);
		// printf_split("out:", *redirection_split);
		if (*redirection_split)
			frees_split(*redirection_split);
		printf("%s", tmp);
		return (-1);
	}
	return (0);
}


int	redirection_check2free(char **temp, char ***redirection_split)
{
	if (*temp != NULL)
		free(*temp);
	if (*redirection_split)
		frees_split(*redirection_split);
	return (-1);
}

int	which_redirection_char(char *temp)
{
	if (!temp && !temp[0])
		return (-1);
	temp = ft_strmchr(temp, "<>");
	if (!temp)
		return (-1);
	if (temp[0] == '<')
		return ('<');
	else if (temp[0] == '>')
		return ('>');
	return (0);
}

char	*get_redirection_command(char *temp, char **redirection_split,
		int iteritor)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (!temp || !redirection_split || !redirection_split[iteritor])
		return (NULL);
	while (i < ft_strlen(temp))
	{
		j = 0;
		if (temp[i] == redirection_split[iteritor][0])
		{
			k = i;
			while (temp[k] && temp[k] == redirection_split[iteritor][j])
			{
				k++;
				j++;
			}
			if (ft_strlen(redirection_split[iteritor]) == j)
				return (temp + k);
		}
		i++;
	}
	return (NULL);
}

int	handle_redirection_segment(char ***redirection_split, char **temp,
		char **temp4, char *th)
{
	if (!temp4)
	{
		redirection_check2free(temp, redirection_split);
		return (-1);
	}
	*temp4 = get_redirection_command(th, *redirection_split, 0);
	if (!(*temp4))
	{
		free(th);
		redirection_check2free(temp, redirection_split);
		return (-1);
	}
	return (0);
}

int	extract_apply_short(char **temp, char **tmp, char ***redirection_split,
		char *temp4_copy)
{
	if (!temp4_copy)
	{
		redirection_check2free(temp, redirection_split);
		return (-1);
	}
	*tmp = ft_strjoin(*temp, " ");
	return (0);
}
void	setup_extra_command_2(char	**split_2, char	**command)
{
	char	*tmp;
    char	*tmp2;
	int		j;
	
	j = 1;
    while (j < (int)element_size(split_2))
    {
        tmp = ft_strjoin(split_2[j], " ");
        if (tmp)
        {
            tmp2 = ft_strjoin(*command, tmp);
            free(tmp);
            if (*command)
                free(*command);
            *command = tmp2;
        }
        j++;
    }
    frees_split(split_2);
}

int		setup_extra_command(char *temp5, char **command)
{
    char	**split;
    char	**split_2;
    int		i;

    split = ft_mult_split(temp5, "<>");
    if (!split)
        return (-1);
    i = 0;
    while (i < (int)element_size(split))
    {
        split_2 = ft_split(split[i], ' ');
		if (!split_2)
		{
			frees_split(split);
        	return (-1);
		}
		if (split_2)
			setup_extra_command_2(split_2, command);
        i++;
    }
    frees_split(split);
	return (0);
}

int	extract_apply_short_2(char *tmp, char *temp5, char *temp4_copy, char **command)
{
	(*command) = ft_strjoin(tmp, temp4_copy);
	setup_extra_command(temp5, command);
	free(tmp);
	free(temp4_copy);
	if (!(*command))
		return (-1);
	return (0);
}

void	extract_apply_short_3(char **tmp, char **temp, char *temp4,
		char **command)
{
	(*tmp) = ft_strjoin(*temp, " ");
	(*command) = ft_strjoin((*tmp), temp4);
	free(*tmp);
}

int	extract_and_apply_redirection(char **temp, char *temp2,
		char ***redirection_split, char **command)
{
	char	*temp4_raw;
	char	*temp4_copy;
	char	*temp4;
	char	*temp5;
	char	*tmp;
	char	*th;
	int		which;

	which = which_redirection_char(temp2 + 1);
	temp4_raw = ft_strmchr(temp2, "<>");
	temp4 = get_redirection_command(temp4_raw, *redirection_split, 0);
	if (which > 0)
	{
		th = ft_strfchr(temp2 + 1, which);
		// ft_printf("%2output:%s\n", temp4);
		temp5 = ft_strmchr(temp4, "<>");
		if (handle_redirection_segment(redirection_split, temp, &temp4, th) < 0)
		{
			free(temp5);
			return (-1);
		}
		temp4_copy = ft_strdup(temp4);
		free(th);
		if (extract_apply_short(temp, &tmp, redirection_split, temp4_copy) < 0)
		{
			free(temp5);
			return (-1);
		}
		if (extract_apply_short_2(tmp, temp5, temp4_copy, command) < 0)
			return (redirection_check2free(temp, redirection_split));
	}
	else
		extract_apply_short_3(&tmp, temp, temp4, command);
	return (0);
}

int		process_redirections(char ***redirection_split, char **robo_env,
		char **temp3)
{
	char	**tty;
	int		ccount;
	int		fd;

	ccount = -1;
	fd = -1;
	tty = ft_mult_split((*temp3), "<>");
	while (++ccount < ft_2dlen(*redirection_split))
	{
		(*temp3) = ft_strmchr((*temp3), "<>");
		if (!(*temp3))
			break ;
		if (ft_execute_redirection(tty, ccount, &fd, (*temp3), robo_env) < 0)
		{
			if (*redirection_split)
				frees_split(*redirection_split);
			if (tty)
				frees_split(tty);
			dprintf(2, "Error: Invalid redirection\n");
			return (-1);
		}
		(*temp3)++;
	}
	frees_split(tty);
	frees_split(*redirection_split);
	return (0);
}

int		setup_handle_redirection(char *input, char ***redirection_split, char **temp, char **temp2)
{
	if (setup_redirection(input, temp, temp2))
		return (-1);
	if (!(*temp2))
	{
		free(*temp);
		return (-1);
	}
	*redirection_split = ft_mult_split(*temp2, "<> ");
	if (!*redirection_split)
	{
		free(*temp);
		free(*temp2);
		return (-1);
	}
	return (0);
}

int		error_redirection(char **redirection_split, char *command, char	*temp2, char *temp)
{
	if (!redirection_split)
	{
		free(command);
		free(temp);
		free(temp2);
		return (-1);
	}	
	return (0);
}

int		error_process_redirection(char ***redirection_split, char **temp, char *input, char **robo_env)
{
	char	*temp3;

	temp3 = ft_strmchr(input, "<>");
	if (!temp3)
	{
		redirection_check2free(temp, redirection_split);
		return (-1);
	}
	if (process_redirections(redirection_split, robo_env, &temp3) < 0)
		return (-1);
	return (0);
}

int		error_ft_execute_redirection(char *temp, char *command, char **robo_env)
{
	if (ft_execve(command, robo_env) == -1)
	{
		if (command)
			free(command);
		if (temp)
			free(temp);
		perror("Command not found");
		return (-1);
	}
	free(command);
	free(temp);
	return (0);
}

int	ft_redirection(char *input, char ***redirection_split, char **robo_env)
{
	char	*temp;
	char	*temp2;
	char	*command;

	if (!input || !robo_env)
		return (-1);
	if (setup_handle_redirection(input, redirection_split, &temp, &temp2) < 0)
		return (-1);
		if (extract_and_apply_redirection(&temp, temp2, redirection_split,
			&command) < 0)
			return (-1);
	if (error_process_redirection(redirection_split, &temp, input, robo_env) < 0)
	{
		if (temp)
			free(temp);
		if (command)
			free(command);
		return (-1);
	}
	if (error_redirection(*redirection_split, command, temp2, temp) < 0)
		return (-1);
	if (error_ft_execute_redirection(temp, command, robo_env) < 0)
		return (-1);
	return (0);
}

/*
int	main(int argc, char *arv[], char **robo_env)
{
	char	*inter;
	char	*temp;
	char	*temp2;
	char	**redirection_split;
	char	**redirection_data_split;
	int		mult;
	char *temp3;

	inter = "ls -l <fin<in < in > fin";
	ft_redirection(inter, &redirection_split, robo_env);
	return (0);
} */