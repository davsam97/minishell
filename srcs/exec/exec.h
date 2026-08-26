/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:13:05 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 11:21:08 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../core/core.h"

// exec_builtins.c
int		is_builtin(char *cmd);
int		execute_builtin(char **args, t_shell *shell);
int		execute_builtin_redir(char **argv, t_redir *redir, t_shell *shell);

// exec_cmd.c
int		execute_simple_command(t_node *node, t_shell *shell);

// exec_pipe.c
int		execute_pipeline(t_node *node, t_shell *shell);

// exec_redir.c
int		handle_redirections(t_redir *redir);

// exec_tree.c
int		execute_subshell(t_node *node, t_shell *shell);
int		execute_tree(t_node *node, t_shell *shell);

// exec_utils.c
void	free_split(char **split);
char	*try_path(char *dir, char *cmd);
char	*get_path(char *cmd, t_shell *shell);
int		get_exit_status(int status);

#endif
