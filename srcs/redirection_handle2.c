/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handle2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:47:14 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/23 20:56:14 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirection_mult(char *input)
{
	int	mult_i[3];
	int	conflect_handle[2];
	int	is_file_enter[2];
	int	ret_mul_ret[2];

	mult_i[2] = 0;
	ret_mul_ret[1] = 0;
	init_check_redirection_mult(mult_i, conflect_handle, is_file_enter);
	while (input[mult_i[2]])
	{
		ret_mul_ret[0] = check_redirection_mult_sign(mult_i, conflect_handle,
				is_file_enter, input);
		if (ret_mul_ret[0] < 0)
			return (-1);
		if (ret_mul_ret[0] == 6)
		{
			ret_mul_ret[1] = ret_mul_ret[0];
			mult_i[2]++;
		}
		mult_i[2]++;
	}
	if ((is_file_enter[1] > 0 && is_file_enter[0] == 0) || mult_i[0] > 1
		|| mult_i[1] > 1 || conflect_handle[0] > 1)
		return (-1);
	return (ret_mul_ret[1]);
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
		if ((element_size((*redirection_split)) == 2 || p == 2) && !*temp)
		{
			*temp = ft_strdup((*redirection_split)[px - 1]);
			return (5);
		}
		if (*temp != NULL)
			free(*temp);
		if (*redirection_split)
			frees_split(*redirection_split);
		printf("%s", tmp);
		return (-1);
	}
	return (0);
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
