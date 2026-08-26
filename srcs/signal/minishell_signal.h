/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:13:35 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 11:13:55 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

void	set_signals_interactive(void);
void	ignore_signals(void);
void	reset_signals(void);

int		is_sigint_received(void);
void	mark_sigint_received(void);
void	clear_sigint_received(void);

#endif
