/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:25:17 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 11:23:28 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include "parse.h"
#include "../core/core.h"
#include "../signal/minishell_signal.h"
#include "../expand/expand.h"
#include "../../libft/libft.h"

void	write_heredoc(int fd, char *del, int do_expand_vars, t_shell *shell)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("\001" BG_MAGENTA "\002" "<<" "\001" RESET "\002 ");
		else
			line = get_next_line_strip_nl(STDIN_FILENO);
		if (!line)
			print_2red("here-doc: got EOF when expected", del);
		if (is_sigint_received() || !line || ft_strcmp(line, del) == 0)
			break ;
		if (do_expand_vars)
			expanded_line = expand_variable(line, shell, 1);
		else
			expanded_line = ft_strdup(line);
		if (!expanded_line)
			break ;
		write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		free(line);
		free(expanded_line);
	}
	free(line);
}

void	call_heredoc(t_node *node, t_ctx_parser *ctx, char *delim
	, int fd[2])
{
	char	*exp_del;

	(void) node;
	if (ft_is_in_set(delim, '"') || ft_is_in_set(delim, '\''))
		exp_del = remove_quotes(delim);
	else
		exp_del = ft_strdup(delim);
	write_heredoc(fd[1], exp_del, !ft_strcmp(delim, exp_del), ctx->shell);
	free(exp_del);
	close(fd[1]);
}

static char	*pretty_prompt(t_ctx_parser *ctx)
{
	int		type;
	char	prompt[32];

	type = ctx->arr_token[ctx->i - 1].type;
	prompt[0] = '\0';
	if (type == TK_OP_AND)
		ft_strlcat(prompt, "\001" BG_GREEN "\002&&", 32);
	else if (type == TK_OP_OR)
		ft_strlcat(prompt, "\001" BG_YELLOW "\002||", 32);
	else if (type == TK_PIPE)
		ft_strlcat(prompt, "\001" BG_RED "\002|", 32);
	else if (type == TK_OPEN_PARENT)
		ft_strlcat(prompt, "\001" BG_BLUE "\002(", 32);
	ft_strlcat(prompt, "\001" RESET "\002 ", 32);
	return (readline(prompt));
}

static int	not_just_empty_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

// Called when the parser hits an unexpected TK_END: reads and tokenizes
// another line, then swaps it into ctx so parsing can continue.
int	command_continuation(t_ctx_parser *ctx)
{
	char	*line;
	t_token	*new_tokens;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = pretty_prompt(ctx);
		else
			line = get_next_line_strip_nl(STDIN_FILENO);
		if (is_sigint_received())
			return (free(line), -1);
		if (!line)
			return (print_red("syntax: unexpected EOF"), -1);
		if (not_just_empty_space(line))
			break ;
		free(line);
	}
	new_tokens = tokenize(line, ctx->shell);
	free(line);
	if (!new_tokens)
		return (-1);
	clean_tokens(&ctx->arr_token);
	ctx->arr_token = new_tokens;
	ctx->i = 0;
	return (0);
}
