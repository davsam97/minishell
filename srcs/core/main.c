/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:25:17 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 12:19:24 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "core.h"
#include "../env/env.h"
#include "../exec/exec.h"
#include "../signal/minishell_signal.h"
#include "../../libft/libft.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = init_env(envp);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	shell->last_exit = 0;
	shell->envp = envp;
	shell->node = NULL;
	shell->is_tty = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
	return (shell);
}

static void	parse_and_run_command(char *str, t_shell *shell)
{
	int		exit_status;

	if (is_sigint_received())
	{
		shell->last_exit = 130;
		clear_sigint_received();
		return ;
	}
	if (!str || !ft_strlen(str))
		return ;
	if (shell->is_tty)
		add_history(str);
	shell->node = get_abstract_syntax_tree(str, shell);
	if (shell->node)
	{
		exit_status = execute_tree(shell->node, shell);
		shell->last_exit = exit_status;
		clean_nodes(&shell->node);
	}
}

static void	main_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (shell->is_tty)
		{
			set_signals_interactive();
			line = readline("🐐🐚> ");
		}
		else
			line = get_next_line_strip_nl(STDIN_FILENO);
		if (!line)
		{
			if (shell->is_tty)
				write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		parse_and_run_command(line, shell);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		exit_code;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	main_loop(shell);
	return (exit_code = shell->last_exit, clean_shell(shell), exit_code);
}
