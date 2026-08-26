/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:25:17 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 12:02:46 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "../core/core.h"
#include "../../libft/libft.h"

void	clean_tokens(t_token **arr_token)
{
	int	i;

	i = 0;
	while ((*arr_token)[i].type != TK_END)
	{
		free((*arr_token)[i].str);
		i++;
	}
	free(*arr_token);
	*arr_token = NULL;
}

// Returns the number of tokens written, or -1 on error.
static int	populate_token(char *str, t_token *arr_token)
{
	int		i;
	int		valid_token;
	int		size;

	i = 0;
	valid_token = -1;
	size = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) || str[i] == '\n')
		{
			i++;
			continue ;
		}
		arr_token[size] = (t_token){NULL, TK_END};
		valid_token = set_token(arr_token, size, str, i);
		if (valid_token == -1)
			return (print_3red("invalid token at index", i, &str[i]), -1);
		i = valid_token;
		size++;
	}
	return (size);
}

// Worst case is one token per character, hence the +1 allocation below.
t_token	*tokenize(char *str, t_shell *shell)
{
	int		size;
	t_token	*arr_token;
	int		failure;

	size = 0;
	failure = 0;
	arr_token = safe_malloc(sizeof(t_token) * (ft_strlen(str) + 1));
	if (!arr_token)
		return (NULL);
	size = populate_token(str, arr_token);
	if (size == -1)
	{
		failure = 1;
		shell->last_exit = 2;
		return (clean_tokens(&arr_token), arr_token);
	}
	arr_token[size] = (t_token){NULL, TK_END};
	if (failure || size == 0)
		clean_tokens(&arr_token);
	return (arr_token);
}
