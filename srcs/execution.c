/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:55:32 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/05 20:26:52 by nqasem           ###   ########.fr       */
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

	i = -1;
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
			(*here_doc)->pryority[i] = 1;
			(*here_doc)->counter++;
		}
		else
			(*here_doc)->pryority[i] = 2;
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
int		here_doc_manger(t_cmd **cmd, char **file_loc)
{
	t_list	*current;
	int		i;
	int		j;

	i = 0;
	j = 0;
	current = (*cmd)->word;
	while ((*cmd)->here_doc->pryority[i] != '\0')
	{
		if ((*cmd)->here_doc->pryority[i] == 1)
		{
				if (heredoc(current->content, &(file_loc[j])))
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
 	// int p = 0;
	// while ((*cmd)->here_doc->pryority[p] != '\0')
	// {
	// 	printf("Command: %d\n", (*cmd)->here_doc->pryority[p]);
	// 	p++;
	// }
int	execution(t_cmd **cmd, char **env)
{
	int		i;
	int		j;
	int		k;
	int		size;
	t_list	*current;

	size = ft_lstsize((*cmd)->word);
	(*cmd)->here_doc->pryority = malloc(sizeof(int) * (size + 1));
	(*cmd)->here_doc->pryority[size] = '\0';
	(*cmd)->who_am_i = 0;	
	(*cmd)->here_doc->index = 0;
	if (searching_here_doc(cmd, &(*cmd)->here_doc) == -1)
	{
			perror("Error in here doc");
			return (-13);
 	}
	char **file_loc = malloc(sizeof(char *) * ((*cmd)->here_doc->counter + 1));
	if (!file_loc)
	{
		perror("malloc");
		return (-1);
	}
	(*cmd)->here_doc->file_loc = file_loc;
	if(here_doc_manger(cmd, (*cmd)->here_doc->file_loc))
		return (-1);

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
	// if(child_process(cmd, &current, pipe_fd2, (pids), file_loc))
	if(child_process(cmd, &current, pipe_fd2,  pids, file_loc))
		return (-1);
	int no = 0;
	while (no < (*cmd)->here_doc->counter)
	{
		unlink((*cmd)->here_doc->file_loc[no]);
		free((*cmd)->here_doc->file_loc[no]);
		no++;
	}
	close_wait(pids, size, pipe_fd2);
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
			if(dup_process(&i, size, pipe_fd2) == -1)
				return (-1);
			if(dup_process_2(cmd, (current), file_loc, i) == -1)
				return (-1);
				dprintf(2, "print: %d\n", (*cmd)->here_doc->index);
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

int		execute_heredoc(char *file, char **ev, int i, char **file_loc)
{
    if (!file_loc[i])
	{
        dprintf(2, "Error: file_loc[%d] is NULL in execute_heredoc\n", i);
        return (-1);
    }
    int fd = open(file_loc[i], O_RDONLY);
    if (fd < 0)
	{
        perror("open heredoc file");
        return (-1);
    }
    int org = dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
	char *temp = ft_strfchr(file, '<');
	if (ft_strlen(temp) <= 1)
		return (0);
    ft_execve(temp, ev);
    return (0);
}

int		dup_process_2(t_cmd **cmd, t_list	**current, char **file_loc, int i)
{
	char	**redirection_split;
	char	**env;
	int		heredoc_idx;

	env = (*cmd)->env;
	if ((*cmd)->here_doc->pryority[i] == 1)
	{
        // heredoc_idx = (*cmd)->here_doc->index;
        // if (execute_heredoc((*current)->content, env, heredoc_idx, file_loc) == -1)
        //     return (-1);
  
	}
	if (ft_strmchr((*current)->content ,"<>") && (*cmd)->who_am_i != 13)
	{
		if(ft_redirection((*current)->content, &redirection_split, env) < 0)
		{
			write(2, "Error: Invalid redirection\n\n", 27);
			return (-1);
		}
	}
	if ((*cmd)->who_am_i == 13)
	{
		write(2, "here doc\n", 9);
		return (-1);
	}
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
