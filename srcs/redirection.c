/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:00:09 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/12 21:49:56 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* 
 void	free_it_now(char **s, char *s2, int emassage)
{
	int	n;

	n = 0;
	if (s2 != NULL)
		free(s2);
	while (s[n])
	{
		free(s[n]);
		n++;
	}
	free(s);
	if (emassage || emassage == -1)
		perror("Error");
}

 int	handle_ecv_slash(char *result, char **m, char **paths)
{
	if (result && ft_strncmp(result, "/", 1) == 0)
	{
		if (access(result, F_OK | X_OK) == 0)
		{
			*m = ft_strdup(result);
			return (5);
		}
		else
		{
			free_it_now(paths, NULL, 0);
			return (-6);
		}
	}
	return (0);
}

 int	check_validation(char **paths, char **result, char **m)
{
	int	ret;

	*m = NULL;
	if (!paths)
	{
		free_it_now(paths, NULL, 1);
		return (-1);
	}
	if (result[0] && ft_strncmp(result[0], "./", 2) == 0)
	{
		if (access(result[0], X_OK) == -1)
		{
			free_it_now(paths, NULL, 0);
			perror("Error: File is not executable or doesn't exist");
			return (1);
		}
		*m = ft_strdup(result[0]);
		return (4);
	}
	ret = handle_ecv_slash(result[0], m, paths);
	if(ret == 5 || ret == -6)
		return (ret);
	*m = check_access(paths, result);
	return (0);
}

 int	get_path(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (ft_strncmp(ev[i], "PATH=/", 6) == 0)
			break ;
		i++;
	}
	return (i);
}

 void	no_space(int *l, char **m, char **o)
{
	*l = -1;
	*o = "/";
	*m = NULL;
}

 char	*check_access(char **paths, char **result)
{
	int		l;
	char	*full_path;
	char	*m;
	char	*o;
	char	*p;

	no_space(&l, &m, &o);
	p = ft_strjoin(o, result[0]);
	while (paths[++l])
	{
		full_path = ft_strjoin(paths[l], p);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			m = ft_strdup(full_path);
			free(full_path);
			break ;
		}
		free(full_path);
	}
	free_it_now(paths, p, 0);
	return (m);
}

 int	ft_setup_execve(char *file, char ***result, char **ev, char ***paths)
{
	*result = ft_split(file, ' ');
	if (!*result)
	{
		perror("Error splitting file");
		return (-1);
	}
	*paths = ft_split(ev[get_path(ev)] + 5, ':');
	if (!*paths)
	{
		free_it_now(*result, NULL, 1);
		return (-1);
	}
	return (0);
}

 int	ft_execve(char *file, char **ev)
{
	char	**result;
	char	**paths;
	int		flag;
	char	*m;

	if(ft_setup_execve(file, &result, ev, &paths) == -1)
		return (-1);
	flag = check_validation(paths, result, &m);
	if (m == NULL || flag < 0)
	{
		free_it_now(result, NULL, 1);
		if (m != NULL)
			free(m);
		return (-1);
	}
	if (execve(m, result, ev) == -1)
	{
		perror("Error executing command");
		free_it_now(result, m, 1);
		return (-1);
	}
	free_it_now(result, m, 0);
	return (0);
}

 void	printf_split(char *str, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("%2%s%s\n", str, split[i]);
		i++;
	}
} */

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

char		*extract_filename(char **redirection_split, int ccount)
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
		ft_printf("%2%c", temp3[0]);

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

int		handle_mult_redirection(char *temp3, char *temp2, char **temp, char ***redirection_split)
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

int		setup_handle_redirection(char *input, char ***redirection_split, char **temp, char **temp2)
{
	if (setup_redirection(input, temp, temp2))
		return (-1);
	if ((*temp2) == NULL)
		return (-1);
	*redirection_split = ft_mult_split((*temp2), "<> ");
	if (*redirection_split == NULL)
	{
		free((*temp));
		free((*temp2));
		return (-1);
	}
	return (0);
}

int		redirection_check2free(char **temp, char ***redirection_split)
{
	if (*temp != NULL)
		free(*temp);
	if (*redirection_split)
		frees_split(*redirection_split);
	return (-1);
}
// size_t	size_spacestring(void){}

int		which_redirection_char(char *temp)
{
	if (!temp && !temp[0])
		return (-1);
	temp = ft_strmchr(temp, "<>");
	if (!temp)
		return (-1);
	if (temp[0] == '<')
		return ('<');
	else if(temp[0] == '>')
		return ('>');
	return (0);
}

char		*get_redirection_command(char *temp, char **redirection_split, int iteritor)
{
	int		i;
	int		j;
	int		k;
	
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
			if(ft_strlen(redirection_split[iteritor]) == j)
				return (temp + k);
		}
		i++;
	}
	return(NULL);
}

int ft_redirection(char *input, char ***redirection_split, char **robo_env)
{
    char *temp = NULL;
    char *temp2 = NULL;
    char *temp3 = NULL;
    char *temp4 = NULL;
    char *command = NULL;
	int fd = -1;
	char **tty;
    int which;
	char *tmp;

    if (!input || !robo_env)
        return (-1);
    if (setup_redirection(input, &temp, &temp2))
        return (-1);
    if (!temp2)
    {
        free(temp);
        return (-1);
    }
    *redirection_split = ft_mult_split(temp2, "<> ");
    if (!*redirection_split)
    {
        free(temp);
        free(temp2);
        return (-1);
    }
    temp3 = ft_strmchr(input, "<>");
    if (!temp3)
    {
        redirection_check2free(&temp, redirection_split);
        return (-1);
    }
    which = which_redirection_char(temp2 + 1);
	char *temp4_raw = ft_strmchr(temp2, "<>");
	temp4 = get_redirection_command(temp4_raw, *redirection_split, 0);

	if (which > 0)
	{
		        char *th = ft_strfchr(temp2 + 1, which);
		if (!temp4)
		{
		    redirection_check2free(&temp, redirection_split);
		    return (-1);
		}
		temp4 = get_redirection_command(th, *redirection_split, 0);
		if (!temp4)
		{
		    free(th);
		    redirection_check2free(&temp, redirection_split);
		    return (-1);
		}
		char *temp4_copy = ft_strdup(temp4);
		free(th);

		if (!temp4_copy)
		{
		    redirection_check2free(&temp, redirection_split);
		    return (-1);
		}

		tmp = ft_strjoin(temp, " ");
		command = ft_strjoin(tmp, temp4_copy);
		free(tmp);
		free(temp4_copy);

			if (!command)
			{
				redirection_check2free(&temp, redirection_split);
				return (-1);
			}
		}
		else
		{
			tmp = ft_strjoin(temp, " ");
			command = ft_strjoin(tmp, temp4);
			free(tmp);
		}
		int ccount=-1;
		tty = ft_mult_split(temp3, "<>");
		while (++ccount < ft_2dlen(*redirection_split))
		{
			temp3 = ft_strmchr(temp3, "<>");
			if (!temp3)
				return (0);
			
			if (ft_execute_redirection(tty, ccount, &fd, temp3, robo_env) < 0)
			{
				if (temp != NULL)
					free(temp);
				if (*redirection_split)
					frees_split(*redirection_split);
				if (tty)
					frees_split(tty);
				dprintf(2, "Error: Invalid redirection\n");
				return (-1);
			}
			temp3++;
		}
		frees_split(tty);
		frees_split(*redirection_split);
		if (!*redirection_split)
		{
			free(command);
			free(temp);
       		free(temp2);
        	return (-1);
    	}

    pid_t a = fork();
    if (a == 0)
    {
        if (ft_execve(command, robo_env) == -1)
        {
            free(command);
            free(temp);
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }
    else if (a < 0)
    {
        perror("Fork failed");
        free(command);
        free(temp);
        return (-1);
    }
	wait(NULL);
    free(command);
    free(temp);
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