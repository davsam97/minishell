/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 08:42:52 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 12:00:51 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expand.h"
#include "../../libft/libft.h"

void	expand_argv_variables(char **argv, t_shell *shell)
{
	int		i;
	char	*str;

	i = 0;
	if (!argv)
		return ;
	while (argv[i] != NULL)
	{
		str = expand_variable(argv[i], shell, 0);
		free(argv[i]);
		argv[i] = str;
		if (!argv[i])
		{
			free_argv(argv);
			print_red("expansion variables failed");
			return ;
		}
		i++;
	}
}

void	expand_argv_quotes(char **argv)
{
	int		i;
	char	*str;

	i = 0;
	if (!argv)
		return ;
	while (argv[i] != NULL)
	{
		str = remove_quotes(argv[i]);
		free(argv[i]);
		argv[i] = str;
		if (!argv[i])
		{
			free_argv(argv);
			print_red("expansion variables failed");
			return ;
		}
		i++;
	}
}

static int	expand_redir_wildcard(t_redir *redir)
{
	char	**matches;

	if (!has_wildcard(redir->filename))
		return (0);
	matches = expand_single_wildcard(redir->filename);
	if (!matches || !matches[0])
		return (0);
	if (matches[1])
	{
		free_argv(matches);
		print_red("minishell: ambiguous redirect");
		return (-1);
	}
	free(redir->filename);
	redir->filename = ft_strdup(matches[0]);
	free_argv(matches);
	return (0);
}

static int	expand_redirections(t_redir *redir, t_shell *shell)
{
	char	*expanded;

	while (redir)
	{
		if (redir->type != TK_REDIR_2IN)
		{
			expanded = expand_variable(redir->filename, shell, 0);
			if (expanded)
			{
				free(redir->filename);
				redir->filename = expanded;
			}
			expanded = remove_quotes(redir->filename);
			if (expanded)
			{
				free(redir->filename);
				redir->filename = expanded;
			}
			if (expand_redir_wildcard(redir) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

int	expand_cmd_node(t_node *node, t_shell *shell)
{
	expand_argv_variables(node->argv, shell);
	handle_empty_args(&node->argv);
	node->argv = expand_wildcards_in_argv(node->argv);
	expand_argv_quotes(node->argv);
	if (!node->argv)
		return (-1);
	if (expand_redirections(node->redir, shell))
		return (-1);
	return (0);
}
