/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:25:17 by dasamuel          #+#    #+#             */
/*   Updated: 2026/01/14 08:52:21 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "parse.h"
#include "../core/core.h"

t_node	*new_node(t_node_type type, t_node *left, t_node *right)
{
	t_node	*node;

	node = safe_malloc(sizeof(t_node));
	if (!node)
		return (clean_nodes(&left), clean_nodes(&right), NULL);
	node->type = type;
	node->argv = NULL;
	node->redir = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

static void	clean_redir(t_node *node)
{
	t_redir	*redir;
	t_redir	*redir_next;

	redir = node->redir;
	while (redir)
	{
		free(redir->filename);
		if (redir->fd != -1)
			close(redir->fd);
		redir_next = redir->next;
		free(redir);
		redir = redir_next;
	}
}

void	clean_nodes(t_node **node_addr)
{
	int		i;
	t_node	*node;

	if (!node_addr || !*node_addr)
		return ;
	node = *node_addr;
	clean_nodes(&node->left);
	clean_nodes(&node->right);
	i = 0;
	while (node->argv && node->argv[i])
		free(node->argv[i++]);
	free(node->argv);
	clean_redir(node);
	free(node);
	*node_addr = NULL;
}
