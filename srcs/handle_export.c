/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:36:24 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/11 11:22:41 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (ft_strcmp(result[x], "<<") == 0 || ft_strcmp(result[x], ">>") == 0)
		{
			x++;
			continue ;
		}
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

static int	setup_export(char *str, t_cmd **cmd, char ***result)
{
	char	*cleaned;

	cleaned = skp(str);
	if (!cleaned)
		return ((*cmd)->exit_status = 1);
	*result = ft_split_custom_exp(cleaned, ' ');
	free(cleaned);
	if (remove_quotues(result))
		return (free_err_ret(NULL, NULL, *result, -1));
	if (!(*result))
		return ((*cmd)->exit_status = 1);
	if (remove_leading_tabs(*result) < 0)
		return (free_err_ret(NULL, NULL, *result, -1));
	return (0);
}

int	ft_export(char *str, t_cmd **cmd)
{
	char	**result;
	t_exp	*export;
	int		i;

	if (handle_ret_export(str, cmd) < 0)
		return (-1);
	if (setup_export(str, cmd, &result) < 0)
		return (-1);
	i = 0;
	while (result[i])
		i++;
	export = init_export(i);
	if (!export)
		free_err_ret("Error: Memory allocation failed\n", NULL, result, -60);
	if (fill_export_manger(&export, result) < 0)
		return (-1);
	robo_export(cmd, export);
	free_exp(export);
	frees_split(result);
	return (0);
}
