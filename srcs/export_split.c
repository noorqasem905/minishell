/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:13:30 by aalquraa          #+#    #+#             */
/*   Updated: 2025/04/30 21:14:34 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int count_tokens(const char *s)
{
	int count = 0;
	int in_token = 0;
	char quote = 0;

	while (*s) {
		if (*s == '"' || *s == '\'') {
			if (!quote)
				quote = *s;
			else if (quote == *s)
				quote = 0;
		}
		else if (!quote && is_space(*s)) {
			in_token = 0;
		}
		else if (!in_token) {
			in_token = 1;
			count++;
		}
		s++;
	}
	return count;
}

static char *extract_token(const char **s) {
	const char *start;
	char quote = 0;
	size_t len = 0;
	char *token;

	while (is_space(**s)) (*s)++;

	start = *s;

	while (**s) {
		if (!quote && (**s == '"' || **s == '\'')) {
			quote = **s;
			(*s)++;
			continue;
		}
		if (quote && **s == quote) {
			quote = 0;
			(*s)++;
			continue;
		}
		if (!quote && is_space(**s))
			break;
		(*s)++;
	}

	len = *s - start;
	token = malloc(len + 1);
	if (!token)
		return NULL;
	strncpy(token, start, len);
	token[len] = '\0';
	return token;
}

char **smart_split(const char *s)
{
	int count = count_tokens(s);
	char **tokens = malloc(sizeof(char *) * (count + 1));
	int i = 0;

	if (!tokens)
		return NULL;

	while (*s && i < count)
    {
		tokens[i] = extract_token(&s);
		if (!tokens[i])
        {
			for (int j = 0; j < i; j++) free(tokens[j]);
			free(tokens);
			return NULL;
		}
		i++;
	}
	tokens[i] = NULL;
	return tokens;
}
