/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:53:42 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 11:53:43 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 1: 001 clean tokens
// 2: 010 clean nodes
// 4: 100 clean shell
void	clean_stuff(t_token **arr_token, t_node **node, t_shell *shell,
		int flag)
{
	if (flag & 1 && arr_token != NULL)
		clean_tokens(arr_token);
	if (flag & 2 && node != NULL)
		clean_nodes(node);
	if (flag & 4 && shell != NULL)
		clean_shell(shell);
}

void	clean_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		clean_env(shell->env);
	if (shell->node)
		clean_nodes(&shell->node);
	free(shell);
}

void	clean_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
