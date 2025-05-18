/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/17 09:44:39 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	print_saved_cmd1(t_list *saved_cmd)
{
	t_list	*current;

	current = saved_cmd;
	while (current != NULL)
	{
		ft_printf("Command: %s\n", (char *)current->content);
		current = current->next;
	}
}

int	set_init(t_cmd **cmd, int size)
{
	int		i;

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

int		ft_strfind(char *str, char *c)
{
	int	i;
	int j;

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

int searching_here_doc(t_cmd **cmd, t_here_doc **here_doc)
{
	t_list	*current;
	int		check_error;
	char	*temp;
	int		i;
	int		p;

	i = -1;
	p = 0;
	current = (*cmd)->word;
	(*here_doc)->counter = 0;
	while (-1 < ++i && current != NULL)
	{
		if (ft_strfind(current->content, "<<"))
		{
			(*cmd)->who_am_i = 13;
			temp = ft_strnstr(current->content, "<<", ft_strlen(current->content));
			check_error = handle_here_doc(temp);
			if (check_error < 0)
			{
				printf("error here doc\n");
				(*cmd)->exit_status = -14;
				return (-1);
			}
			(*here_doc)->pryority[i] = 2 + p;
			(*here_doc)->counter++;
			p++;
		}
		else
			(*here_doc)->pryority[i] = 1;
		current = current->next;
	}
 	(*here_doc)->pryority[i] = '\0';
	return (0);
}

void pprintf(char **str)
{
	int no = 0;
	while (str[no])
	{
		dprintf(2,"out: %s\n", str[no]);
		no++;
	}
}

int		sizeof_heredoc(char *str)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '<' && str[i + 1] == '<')
		{
			size++;
			i++;
		}
		i++;
	}
	return (size);
}

int		here_doc_manger(t_cmd **cmd, char **file_loc)
{
	t_list	*current;
	int		num_here_doc;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	current = (*cmd)->word;
	while ((*cmd)->here_doc->pryority[i] != '\0')
	{
		if ((*cmd)->here_doc->pryority[i] >= 2)
		{
				size = sizeof_heredoc(current->content);
				if (size > 1023 || heredoc(current->content, &(file_loc[j]), size) < 0)
				{
					perror("heredoc");
					return (-1);
				}
				j++;
		}
		current = current->next;
		i++;
	}
	
	return (0);
}

int	execution(t_cmd **cmd, char **env)
{
	int		i;
	int		j;
	int		k;
	int		size;
	t_list	*current;
	char **file_loc;

	size = ft_lstsize((*cmd)->word);
	(*cmd)->here_doc->pryority = NULL;
	if (size > 300)
		return (65);
	(*cmd)->here_doc->pryority = malloc(sizeof(int) * (size + 1));
	(*cmd)->here_doc->pryority[size] = '\0';
	(*cmd)->who_am_i = 0;	
	(*cmd)->here_doc->index = 0;
	if (searching_here_doc(cmd, &(*cmd)->here_doc) == -1)
	{
			perror("Error in here doc");
			return (-13);
 	}
	file_loc = NULL;
	if ((*cmd)->here_doc->counter > 0)
	{
		file_loc = malloc(sizeof(char *) * ((*cmd)->here_doc->counter + 1));
		if (!file_loc)
		{
			perror("malloc");
			return (-1);
		}
		(*cmd)->here_doc->file_loc = file_loc;
		if(here_doc_manger(cmd, (*cmd)->here_doc->file_loc))
			return (65);
	}
	pid_t	pids[size];
	int		pipe_fd2[size][2];
	current = (*cmd)->word;
	i = 0;
	j = 0;
	if (!cmd || !(*cmd) || !(*cmd)->word)
	{
		perror("Invalid command structure");
		return (-1);
	}
	if (size == 0)
	{
		perror("No commands to execute");
		return (-1);
	}
	while (i < size - 1)
	{
		if (pipe(pipe_fd2[i]) == -1)
		{
		    dprintf(2, "pipe failed at index %d\n", i);
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if(child_process(cmd, &current, pipe_fd2,  pids, file_loc))
		return (-1);
	close_wait(pids, size, pipe_fd2);
    int no = 0;
    while (no < (*cmd)->here_doc->counter)
    {
        if ((*cmd)->here_doc->file_loc[no]) 
		{
            unlink((*cmd)->here_doc->file_loc[no]);
            free((*cmd)->here_doc->file_loc[no]);
        }
        no++;
    }
	if (file_loc)
	{
    	free((*cmd)->here_doc->file_loc);
    	(*cmd)->here_doc->file_loc = NULL;
	}
	return (0);
}

void	run_export_execution(char **run)
{
	int	i;

	i = 0;
	while (run[i])
	{
		ft_printf("%s\n", run[i]);
		i++;
	}
}
int		run_buildin_execution(t_cmd	*cmd, t_list *current)
{
	char	*tmp;

	tmp = ft_strtrim(current->content , " ");
	if (!tmp)
		return (-1);
	if (ft_strcmp(tmp, "export") == 0 || ft_strcmp(tmp, "env") == 0)
	{
		free(tmp);
		run_export_execution(cmd->env);
		return (-1);
	}
	free(tmp);
	return (0);
}
int		child_process(t_cmd **cmd, t_list	**current,  int pipe_fd2[][2], pid_t pids[], char **file_loc)
{
	int		size;
	int		i;
	
	i = 0;
	size = ft_lstsize((*cmd)->word);
	while (i < size)
	{
		(pids)[i] = fork();
		if ((pids)[i] < 0)
		{
			perror("fork");
			return (-1);
		}
		if ((pids)[i] == 0)
		{
			if (i != 0)
			{
				if (dup2(pipe_fd2[i - 1][0], STDIN_FILENO) == -1)
				{
					dprintf(2, "pipe failed at index %d\n", i);
					perror("dup2");
 					return (-1);
				}
			}
			if (i != size - 1)
			{
				if (dup2(pipe_fd2[i][1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					return (-1);
				}
			}
			j = 0;
			while (j < size - 1)
			{
 					close(pipe_fd2[j][0]);
 					close(pipe_fd2[j][1]);
				j++;
			}
			if (ft_strmchr(current->content ,"<>") && (*cmd)->who_am_i != 13)
			{
				if(ft_redirection(current->content, &redirection_split, env, cmd) < 0)
				{
					write(2, "Error: Invalid redirection\n\n", 27);
					return (-1);
				}
			}
			if ((*cmd)->who_am_i == 13)
			{
				{
					write(2, "here doc\n", 9);
					return (-1);
				}
			}
			if (ft_execve(current->content, env, cmd) == -1 || (*cmd)->flag)
			{
				perror("Command not found");
 				return (-1);
			}
			if(dup_process(&i, size, pipe_fd2) == -1)
				return (-1);
			if(dup_process_2(cmd, (current), file_loc, i) == -1)
				return (-1);
		}
		if (i > 0)
			close(pipe_fd2[i - 1][0]);
		if (i < size - 1)
			close(pipe_fd2[i][1]);
		(*current) = (*current)->next;
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
	free(*command);
	*command = tmp;
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

int		setup_extra_command_h(char *temp5, char **command)
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
			setup_extra_command_h_2(split_2, command);		
        i++;
    }
    frees_split(split);
	return (0);
}

int manager_execution_heredoc(char *file, char **temp)
{
	char	*command;
	int		which;

	which = which_redirection_char(file);
	command = ft_strfchr(file, which);
	// command = ft_strdup(" ");
	// ft_printf("%2-->OUT: %s\n", file);
	if (setup_extra_command_h(file, &command))
	{
		free(command);
		return (-1);
	}
	// ft_printf("%2Final command: %s\n", command);
	*temp = command;
	return (0);
}

int		ft_heredoc_redirection_process(char **str, char *temp)
{
	char	*st;
	char	*tmp;
	char	*tmp2;
	int		ret;
	int		i;

	i = 1;//<       in    <
	while (isspace(temp[i]))
		i++;
	if(temp[i] == '\0' || temp[i] == '<' || temp[i] == '>')
		return (-1);
	st = ft_strmfchr(temp + i, " <>");
	ret = which_redirection_char(temp);
	if (ret == '<')
		tmp = ft_strjoin("<", st);
	else
		tmp = ft_strjoin(">", st);
	free(st);
	st = tmp;
	tmp2 = ft_strjoin(*str, st);
	free(st);
	free(*str);
	*str = tmp2;
	return (0);
}
int		ft_heredoc_redirection_manager(char *file, char **str)
{
    char	*tmp2;
    char	*tmp;
    char	*st;

	*str = NULL;
    tmp = ft_strmchr(file, "<>");
    while (tmp != NULL)
    {
        if (tmp && tmp[1] != '<' && (tmp[0] =='<' || tmp[0] == '>'))
        {
            ft_heredoc_redirection_process(str, tmp);
            tmp2 = ft_strmchr(tmp + 1, "<>");
            tmp = tmp2;
        }
        else
        {
            tmp2 = ft_strmchr(tmp + 2, "<>");
            tmp = tmp2;
        }
    }
    return (0);
}

int		execute_heredoc(char *file, char **ev, int i, char **file_loc)
{
	char 	**redirection_split;
	char	*temp;
	char	*str;
	char	*st;
    int		fd;
	
	if (!file_loc[i])
    {
        dprintf(2, "Error: file_loc[%d] is NULL in execute_heredoc\n", i);
        return (-1);
    }
    fd = open(file_loc[i], O_RDONLY);
	free(file_loc[i]);
    if (fd < 0)
    {
		perror("open heredoc file");
        return (-1);
    }
    dup2(fd, STDIN_FILENO);
	if(manager_execution_heredoc(file, &temp) < 0)
	{
		free(temp);
		return (-1);
	}
	close(fd);
	if(ft_heredoc_redirection_manager(file, &str) < 0)
	{
		free(temp);
		free(str);
		return (-1);
	}
	if (!str)
	{
		if(ft_execve(temp, ev))
		{
			if (temp)
				free(temp);
			return (-1);
		}
	}
	st = ft_strjoin(temp, str);
	if(ft_redirection(st, &redirection_split, ev) < 0)
	{
		if (temp)
			free(temp);
		if (str)
			free(str);
		if (st)
			free(st);
		return (-1);
	}
    free(temp);
	if (str)
		free(str);
	if (st)
		free(st);
    return (0);
}
int		dup_process_2(t_cmd **cmd, t_list **current, char **file_loc, int i)
{
	char	**redirection_split;
	char	**env;
	int		heredoc_idx;

	env = (*cmd)->env;
	if ((*cmd)->here_doc->pryority[i] >= 2)
	{
        heredoc_idx = (*cmd)->here_doc->pryority[i] - 2;
        if (execute_heredoc((*current)->content, env, heredoc_idx, file_loc) == -1)
            return (-1);
	}
	if (ft_strmchr((*current)->content ,"<>") && (*cmd)->who_am_i != 13)
	{
		if(ft_redirection((*current)->content, &redirection_split, env) < 0)
		{
			write(2, "Error: Invalid redirection\n\n", 27);
			return (-1);
		}
	}
	if (run_buildin_execution(*cmd, *current) < 0)
		return (-1);
	if (ft_execve((*current)->content, env) == -1)
	{
		perror("Command not found");
		return (-1);
	}
	return (0);
}

int		dup_process(int *i, int size, int pipe_fd2[][2])
{
	int		j;

	if ((*i) != 0)
	{
		if (dup2(pipe_fd2[(*i) - 1][0], STDIN_FILENO) == -1)
		{
			dprintf(2, "pipe failed at index %d\n", (*i));
			perror("dup2");
			 return (-1);
		}
	}
	if ((*i) != size - 1)
	{
		if (dup2(pipe_fd2[(*i)][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
	}
	j = 0;
	while (j < size - 1)
	{
		close(pipe_fd2[j][0]);
		close(pipe_fd2[j][1]);
		j++;
	}
	return (0);
}

void	close_wait(pid_t	pids[], int size, int pipe_fd2[][2])
{
	int 	i;
	int 	j;
	int		status;

	j = 0;
	while (j < size - 1)
	{
		close(pipe_fd2[j][0]);
		close(pipe_fd2[j][1]);
		j++;
	}
	i = -1;
	while (++i < size && pids[i] && pids[i] != -1)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	        fprintf(stderr, "Error: Command failed with status %d\n", WEXITSTATUS(status));
	}
}
