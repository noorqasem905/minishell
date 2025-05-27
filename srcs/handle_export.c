/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:36:24 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/27 22:02:29 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	remove_leading_tabs(char **result)
{
	char	*tmp;
	int		m;
	int		kk;

	m = 0;
	while (result[0] && result[0][m] == '\t')
		m++;
	if (m > 0)
	{
		tmp = malloc(ft_strlen(result[0]) - m + 1);
		if (!tmp)
			return (-1);
		kk = 0;
		while (result[0][m])
			tmp[kk++] = result[0][m++];
		tmp[kk] = '\0';
		free(result[0]);
		result[0] = tmp;
	}
	return (0);
}

static int	handle_key_value_pair(t_exp *export, char **result, int *x, int *j)
{
	int	len;

	if (result[*x + 1] && result[*x + 1][0] == '=')
	{
		export->name[*j] = ft_strdup(result[*x]);
		export->value[*j] = trim_quotes(result[*x + 1] + 1);
		(*x)++;
	}
	else if (ft_strchr(result[*x], '='))
	{
		len = word_lenn(result[*x], '=');
		export->name[*j] = ft_substr(result[*x], 0, len);
		export->value[*j] = trim_quotes(result[*x] + len + 1);
	}
	else
	{
		export->name[*j] = ft_strdup(result[*x]);
		export->value[*j] = ft_strdup("");
	}
	if (!export->name[*j] || !export->name[*j])
	{
		free_err_ret(NULL, export->name[*j], NULL, -1);
		return (free_err_ret(NULL, export->value[*j], NULL, -1));
	}
	return (0);
}

static int	fill_export(t_exp *export, char **result)
{
	int	x;
	int	j;

	x = 1;
	j = 0;
	while (result[x])
	{
		if (handle_key_value_pair(export, result, &x, &j) < 0)
			return (-1);
		x++;
		j++;
	}
	export->name[j] = NULL;
	export->value[j] = NULL;
	return (0);
}

static int	fill_export_manger(t_exp **export, char **result)
{
	if (fill_export(*export, result) < 0)
	{
		free((*export)->name);
		free((*export)->value);
		free((*export));
		return (free_err_ret(NULL, NULL, result, -1));
	}
	return (0);
}

int	ft_export(char *str, t_cmd **cmd)
{
	char	**result;
	t_exp	*export;
	int		i;

	result = ft_split_custom_exp(str, ' ');
	if (!result)
		return ((*cmd)->exit_status = 1);
	if (remove_leading_tabs(result) < 0)
		return (free_err_ret(NULL, NULL, result, -1));
	i = 0;
	while (result[i])
		i++;
	export = init_export(i);
	if (!export)
	{
		ft_printf("%2Error: Memory allocation failed\n");
		frees_split(result);
		return (-60);
	}
	if (fill_export_manger(&export, result) < 0)
		return (-1);
	robo_export(cmd, export);
	free_exp(export);
	frees_split(result);
	return (0);
}
