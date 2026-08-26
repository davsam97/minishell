/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:12:27 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 11:20:28 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "../parse/parse.h"
# include "../signal/minishell_signal.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_ctx_parser	*ctx;
	t_node			*node;
	char			**envp;
	t_env			*env;
	int				is_tty;
	int				last_exit;
}	t_shell;

// main.c
t_shell	*init_shell(char **envp);

// clean.c
void	clean_shell(t_shell *shell);
void	clean_env(t_env *env);
void	free_argv(char **argv);
void	clean_stuff(t_token **arr_token, t_node **node, t_shell *shell,
			int flag);

// error.c
void	print_red(char *str);
void	print_2red(char *arg1, char *arg2);
void	print_3red(char *arg1, int i, char *arg3);
void	*safe_malloc(size_t __size);

#endif
