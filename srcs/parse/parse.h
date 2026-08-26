/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 12:02:18 by dasamuel          #+#    #+#             */
/*   Updated: 2026/08/26 12:02:19 by dasamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_shell	t_shell;

typedef enum e_token_type
{
	TK_WORD = 1,
	TK_PIPE = 2,
	TK_REDIR_IN = 4,
	TK_REDIR_OUT = 8,
	TK_REDIR_2IN = 16,
	TK_REDIR_2OUT = 32,
	TK_OP_AND = 64,
	TK_OP_OR = 128,
	TK_OPEN_PARENT = 256,
	TK_CLOSE_PARENT = 512,
	TK_END = 1024,
}	t_token_type;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL,
}	t_node_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
}	t_token;

// Linked list of redirections
// FILENAME has a file name or heredoc delimiter
// FD is only valid for TK_REDIR_2IN (heredoc)
typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	int				fd;
	struct s_redir	*next;
}	t_redir;

// ARGV and REDIR are only valid for CMD nodes
typedef struct s_node
{
	t_node_type		type;
	char			**argv;
	t_redir			*redir;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_ctx_parser
{
	t_shell	*shell;
	t_token	*arr_token;
	int		i;
}	t_ctx_parser;

// multiline.c
int		command_continuation(t_ctx_parser *ctx);
void	call_heredoc(t_node *node, t_ctx_parser *ctx, char *delim,
			int fd[2]);
void	write_heredoc(int fd, char *del, int do_expand_vars, t_shell *shell);

// token.c / token_internal.c
t_token	*tokenize(char *str, t_shell *shell);
int		set_token(t_token *arr_token, int arr_i, char *str, int start);
void	clean_tokens(t_token **arr_token);

// node.c
t_node	*new_node(t_node_type type, t_node *left, t_node *right);
void	clean_nodes(t_node **node_addr);

// parse.c
t_node	*get_abstract_syntax_tree(char *str, t_shell *shell);
t_node	*parse_expression(t_ctx_parser *ctx);
t_node	*parse_pipeline(t_ctx_parser *ctx);
t_node	*new_subshell(t_node *node);
t_node	*parse_command(t_ctx_parser *ctx);

// parse_cmd.c
t_node	*parse_simple_command(t_ctx_parser *ctx);

// get_next_line.c
char	*get_next_line_strip_nl(int fd);

#endif
