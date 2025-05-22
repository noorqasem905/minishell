/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:37:38 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/22 19:09:09 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_check_redirection_mult(int mult[], int conflect_handle[],
		int is_file_enter[])
{
	int	iter;

	iter = 0;
	mult[2] = 0;
	while (iter < 2)
	{
		mult[iter] = 0;
		conflect_handle[iter] = 0;
		is_file_enter[iter] = 0;
		iter++;
	}
}

int	check_redirection_mult_sigls(int mult[], int conflect_handle[],
		int is_file_enter[], char *input)
{
	mult[0]++;
	conflect_handle[0]++;
	if (is_file_enter[1] > 0 && is_file_enter[0] == 0)
		return (-1);
	is_file_enter[1] = 1;
	is_file_enter[0] = 0;
	if (input[mult[2] + 1] == '<' && conflect_handle[1] == 0)
	{
		mult[2]++;
		conflect_handle[1] = 1;
	}
	if (input[mult[2] + 1] == '>')
		return (-1);
	return (0);
}

int	check_redirection_mult_siggr(int mult[], int conflect_handle[],
		int is_file_enter[], char *input)
{
	mult[1]++;
	conflect_handle[0]++;
	if (is_file_enter[1] > 0 && is_file_enter[0] == 0)
		return (-1);
	is_file_enter[1] = 2;
	is_file_enter[0] = 0;
	if (input[mult[2] + 1] == '>' && conflect_handle[1] == 0)
	{
		mult[2]++;
		conflect_handle[1] = 1;
	}
	if (input[mult[2] + 1] == '<')
		return (-1);
	return (0);
}

void	check_redirection_mult_nosiggrle(int mult[], int conflect_handle[],
		int is_file_enter[], char *input)
{
	conflect_handle[0] = 0;
	mult[1] = 0;
	mult[0] = 0;
	is_file_enter[1] = 0;
	is_file_enter[0] = 1;
}

int	check_redirection_mult_sign(int mult[], int conflect_handle[],
		int is_file_enter[], char *input)
{
	int ret;

	ret = 0;
	if (input[mult[2]] == '<')
	{
		if (check_redirection_mult_sigls(mult, conflect_handle, is_file_enter,
				input) < 0)
			return (-1);
	}
	else if (input[mult[2]] == '>')
	{
		if (input[mult[2] + 1] == '>' && input[mult[2] + 2] != '>')
		{
			input[mult[2] + 1] = ' ';
			ret = 6;
		}
		if (check_redirection_mult_siggr(mult, conflect_handle, is_file_enter,
				input) < 0)
			return (-1);
	}
	else if (input[mult[2]] != ' ' && input[mult[2]] != '>'
		&& input[mult[2]] != '<')
		check_redirection_mult_nosiggrle(mult, conflect_handle, is_file_enter,
			input);
	return (ret);
}
