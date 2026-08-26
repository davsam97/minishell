/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:12:49 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 11:17:41 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../core/core.h"

// builtin_cd.c
int		cd_with_path(char **args, t_shell *shell);
int		ft_cd(char **args, t_shell *shell);

// builtin_echo.c
int		ft_echo(char **args);

// builtin_env.c
int		ft_env(t_shell *shell);

// builtin_exit.c
void	invalid_args(char *args, t_shell *shell);
int		ft_exit(char **args, t_shell *shell);

// builtin_export.c
int		is_valid_identifier(char *s);
void	print_export_error(char *arg);
int		ft_export(char **args, t_shell *shell);

// builtin_pwd.c
int		ft_pwd(t_shell *shell);

// builtin_unset.c
void	unset_env_value(t_shell *shell, char *key);
int		ft_unset(char **args, t_shell *shell);

#endif
