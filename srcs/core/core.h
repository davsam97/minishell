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

# include <stdlib.h>
# include "../parse/parse.h"

# define BLACK   "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"
# define BOLD "\033[1m"

# define BG_BLACK   "\033[40m"
# define BG_RED     "\033[41m"
# define BG_GREEN   "\033[42m"
# define BG_YELLOW  "\033[43m"
# define BG_BLUE    "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN    "\033[46m"
# define BG_WHITE   "\033[47m"

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
