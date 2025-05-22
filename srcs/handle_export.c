/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:36:24 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/22 22:38:34 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	remove_leading_tabs(char **result)
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
			return ;
		kk = 0;
		while (result[0][m])
			tmp[kk++] = result[0][m++];
		tmp[kk] = '\0';
		free(result[0]);
		result[0] = tmp;
	}
}

static t_exp	*init_export(int count)
{
	t_exp	*export;

	export = malloc(sizeof(t_exp));
	if (!export)
		return (NULL);
	export->name = ft_calloc(count + 1, sizeof(char *));
	export->value = ft_calloc(count + 1, sizeof(char *));
	if (!export->name || !export->value)
	{
		if (export->name)
			free(export->name);
		if (export->value)
			free(export->value);
		free(export);
		return (NULL);
	}
	return (export);
}

static void	handle_key_value_pair(t_exp *export, char **result, int *x, int *j)
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
}

static void	fill_export(t_exp *export, char **result)
{
	int	x;
	int	j;

	x = 1;
	j = 0;
	while (result[x])
	{
		handle_key_value_pair(export, result, &x, &j);
		x++;
		j++;
	}
	export->name[j] = NULL;
	export->value[j] = NULL;
}

int	ft_export(char *str, t_cmd **cmd)
{
	char	**result;
	t_exp	*export;
	int		i;

	result = ft_split_custom_exp(str, ' ');
	if (!result)
		return ((*cmd)->exit_status = 1);
	remove_leading_tabs(result);
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
	fill_export(export, result);
	robo_export(cmd, export);
	//printf_split("NAME: ", export->name);
	//printf_split("VALUE: ", export->value);
	free_exp(export);
	frees_split(result);
	return (0);
}

/* 
int	ft_export(char *str, t_cmd **cmd)
{
	char	**result;
	t_exp	*export;
	int		i;
	int		len;
	int		m;
	char	*tmp;
	int		kk;
	int		x;
	int		y;
	int		j;
	len = 0;
	result = ft_split_custom_exp(str, ' ');
	if (result == NULL)
	{
		ft_printf("%2Error: ft_split failed\n");
		(*cmd)->exit_status = 2;
		return (1);
	}
	m = 0;
	while (result[0] && result[0][m] == '\t')
		m++;
	if (m > 0)
	{
		tmp = malloc(ft_strlen(result[0]) - m + 1);
		if (!tmp)
		{
			ft_printf("%2Error: Memory allocation failed for tmp\n");
			frees_split(result);
			return (1);
		}
		kk = 0;
		while (result[0][m])
		{
			tmp[kk] = result[0][m];
			kk++;
			m++;
		}
		tmp[kk] = '\0';
		free(result[0]);
		result[0] = tmp;
	}
	i = 0;
	while (result[i])
		i++;
	export = malloc(sizeof(t_exp));
	export->name = ft_calloc(i + 1, sizeof(char *));
	export->value = ft_calloc(i + 1, sizeof(char *));
	if (!export->name || !export->value)
	{
		ft_printf("%2Error: Memory allocation failed\n");
		if (export->name)
			free(export->name);
		if (export->value)
			free(export->value);
		free(export);
		frees_split(result);
		return (-60);
	}
	x = 1;
	y = 0;
	j = 0;
	while (result[x])
	{
		if (result[x + 1] && result[x + 1][0] == '=')
		{
			export->name[j] = ft_strdup(result[x]);
			export->value[j] = trim_quotes(result[x + 1] + 1);
			x++;
		}
		else if (ft_strchr(result[x], '='))
		{
			len = word_lenn(result[x], '=');
			export->name[j] = ft_substr(result[x], 0, len);
			export->value[j] = trim_quotes(result[x] + len + 1);
		}
		else
		{
			export->name[j] = ft_strdup(result[x]);
			export->value[j] = ft_strdup("");
		}
		x++;
		j++;
	}
	export->name[j] = NULL;
	export->value[j] = NULL;
	robo_export(cmd, export);
	frees_newsplit(export->name);
	frees_newsplit(export->value);
	free(export);
	frees_split(result);
	return (0);
} */
// printf("%d\n", j);
// 
// printf("%s", export->name[0]);
// printf("*****export*********\n");