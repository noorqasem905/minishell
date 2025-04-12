/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/12 17:36:22 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/minishell.h"

int	save_data(char **input, t_cmd **cmd, int *flag, char ***temp)
{
	int	size;
	int	iterator;

	*flag = 0;
	*temp = ft_split(*input, '|');
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

int     process_input(t_cmd **cmd, int *flag, char ***temp, char **input,  char **robo_env)
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
    expander_input((*cmd)->word, robo_env);
    print_saved_cmd((*cmd)->word);
    if (searching_comand(input, *temp) == -1)
    {
        free(*input);
        return (-1);
    }
    return (0);
}

int reading_manager(t_cmd **cmd, int *flag, char ***temp, char **robo_env)
{
    char *input;
    int ret;


    
    while ((input = readline("Roboshell> ")) != NULL)
    {
        ret = process_input(cmd, flag, temp, &input, robo_env);
        if (ret == -1)
            break;
        else if (ret == -3)
        {
            *flag = 0;
            continue;
        }
        frees_split(*temp);
        frees((&(*cmd)->word));
    }
    printf("Exiting...\n");
    return (0);
}
