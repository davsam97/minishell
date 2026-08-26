/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:13:11 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 11:21:22 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../core/core.h"

// expand_node.c
void	expand_argv_variables(char **argv, t_shell *shell);
void	expand_argv_quotes(char **argv);
int		expand_cmd_node(t_node *node, t_shell *shell);

// expand_utils.c
int		is_var_char(char c);
char	*extract_var_name(char *s, int i);
char	*get_var_value(t_shell *shell, char *var_name);
char	*append_to_result(char *result, char *to_add);
void	update_quote_state(char c, int *in_single, int *in_double);

// expand_utils2.c
void	handle_empty_args(char ***argv);

// expand_var.c
char	*remove_quotes(char *s);
char	*expand_variable(char *s, t_shell *shell, int ignore_quotes);

// expand_wildcards.c
char	**expand_wildcards_in_argv(char **argv);

// expand_wildcards_utils.c
int		has_wildcard(char *str);
int		match_pattern(char *str, char *pattern);
int		count_matches(char *pattern);
void	fill_matches(char *pattern, char **matches);
void	sort_matches(char **matches);

// expand_wildcards_utils2.c
char	**expand_single_wildcard(char *arg);
int		count_matches_for_arg(char *arg);
int		count_total_args(char **argv);

#endif
