/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:12:58 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 11:51:46 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../core/core.h"

// env_init.c
t_env	*new_env_node(char *key, char *value);
void	add_env_node(t_env **env, t_env *nv);
char	*extract_key(char *s);
char	*extract_value(char *s);
t_env	*init_env(char **envp);

// env_set.c
t_env	*find_env_node(t_env *env, char *key);
void	set_env_value(t_shell *shell, char *key, char *value);

// env_utils.c
int		count_env(t_env *env);
char	**env_to_array(t_shell *shell);
char	*get_env_value(t_shell *shell, char *key);

#endif
