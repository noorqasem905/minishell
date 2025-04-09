/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:07:11 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/09 20:21:20 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_input(char **input)
{
	size_t	length;
	char	*read;

	ft_printf("Roboshell> ");
	read = get_next_line(0);
	if (read == NULL)
		return (-1);
	length = ft_strlen(read);
	(*input) = ft_strdup(read);
	free(read);
	if ((*input) == NULL)
		return (-1);
	if (length > 0 && (*input)[length - 1] == '\n')
		(*input)[length - 1] = '\0';
	return (0);
}

int	save_data(char **input, t_cmd **cmd, int *flag, char ***temp)
{
	int	size;
	int	iterator;

	*flag = 0;
	*temp = ft_split(*input, ' ');
	free(*input);
	if (*temp == NULL)
		return (-1);
	size = ft_2dlen(*temp);
    if (size == 0)
        return (*flag = -3);
	(*cmd)->word = NULL;
	iterator = -1;
	while (++iterator < size)
	{
		if ((*temp)[iterator] != NULL)
		{
			insertend(&((*cmd)->word), (*temp)[iterator], flag);
			if (*flag == 12)
				break ;
		}
	}
	return (0);
}
void print_saved_cmd(t_list *saved_cmd) {
    t_list *current = saved_cmd;
    while (current != NULL) {
        ft_printf("Command: %s\n", (char *)current->content);
        current = current->next;
    }
}

int     process_input(t_cmd **cmd, int *flag, char ***temp, char **input)
{
    if (*input)
        add_history(*input);
	if (save_data(input, cmd, flag, temp) == -1 || *flag == -3)
	{
        if (*flag == -3)
        {   
            frees_split(*temp);
            return (-3);
        }
        perror("save_data");
        free(*input);
		return (-1);
	}
    if (searching_comand(input, *temp) == -1)
    {
        free(*input);
        return (-1);
    }
    return (0);
}

int reading_manager(t_cmd **cmd, int *flag, char ***temp)
{
    char *input;
    int ret;

    while ((input = readline("Roboshell> ")) != NULL)
    {
        ret = process_input(cmd, flag, temp, &input);
        if (ret == -1)
            break;
        else if (ret == -3)
        {
            *flag = 0;
            continue;
        }
        print_saved_cmd((*cmd)->word);
        printf("Command saved successfully.\n");
        printf("%s\n", temp[0][0]);  
        frees_split(*temp);
        frees((&(*cmd)->word));
    }
    printf("Exiting...\n");
    return (0);
}
