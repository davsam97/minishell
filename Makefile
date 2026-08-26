# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dasamuel <dasamuel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 15:04:13 by wiwu              #+#    #+#              #
#    Updated: 2026/08/26 11:45:11 by dasamuel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN	= \033[0;32m
RED		= \033[0;31m
RESET	= \033[0m
TITLE	= \033[1;32m

NAME		=	minishell

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g3 -MMD -MP

LINK_FLAG	=	-lreadline

RM			=	rm -rf

SRC_FILES	=	builtins/builtin_cd.c				\
				builtins/builtin_echo.c				\
				builtins/builtin_env.c				\
				builtins/builtin_exit.c				\
				builtins/builtin_export.c			\
				builtins/builtin_pwd.c				\
				builtins/builtin_unset.c			\
				core/clean.c						\
				core/error.c						\
				core/main.c							\
				env/env_init.c						\
				env/env_set.c						\
				env/env_utils.c						\
				exec/exec_builtins.c				\
				exec/exec_cmd.c						\
				exec/exec_redir.c					\
				exec/exec_pipe.c					\
				exec/exec_tree.c					\
				exec/exec_utils.c					\
				expand/expand_utils.c				\
				expand/expand_utils2.c				\
				expand/expand_var.c					\
				expand/expand_node.c				\
				expand/expand_wildcards.c			\
				expand/expand_wildcards_utils.c		\
				expand/expand_wildcards_utils2.c	\
				parse/get_next_line.c				\
				parse/parse.c						\
				parse/multiline.c					\
				parse/token.c						\
				parse/token_internal.c				\
				parse/node.c						\
				parse/parse_cmd.c					\
				signal/signal_set.c					\
				signal/signal.c						\

OBJ_FILES	=	$(SRC_FILES:.c=.o)
SRC_PATH	=	srcs/
OBJ_PATH	=	build/

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SOURCES	= $(addprefix $(SRC_PATH),$(SRC_FILES))
OBJECTS	= $(addprefix $(OBJ_PATH),$(OBJ_FILES))
DEPS	= $(OBJECTS:.o=.d)

# RULES

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_A) $(LINK_FLAG) -o $(NAME)

	@printf "$(GREEN)✔ Successfully compiled$(RESET)\n"
	@echo

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

$(LIBFT_A):

	@printf "$(TITLE)\n"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "  ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗     ██╗"
	@echo "  ████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║     ██║"
	@echo "  ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║     ██║"
	@echo "  ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║     ██║"
	@echo "  ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗███████╗"
	@echo "  ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝╚══════╝"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@printf "$(RESET)Made by $(RED)wiwu$(RESET) and $(RED)dasamuel$(RESET)\n"
	@echo

	@$(MAKE) --silent -C $(LIBFT_DIR)
	
clean:
	@$(RM) $(OBJ_PATH)
	@$(MAKE) --silent -C $(LIBFT_DIR) clean

	@printf "$(GREEN)✔ Object files successfully deleted$(RESET)\n"
	@echo

fclean: clean
	@$(RM) $(NAME) $(NAME)_bonus
	@$(MAKE) --silent -C $(LIBFT_DIR) fclean

	@printf "$(GREEN)✔ Executable successfully deleted$(RESET)\n"

re: fclean all

bonus: $(NAME)_bonus

$(NAME)_bonus: $(OBJECTS) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_A) $(LINK_FLAG) -o $(NAME)_bonus
	@printf "$(GREEN)✔ Successfully compiled$(RESET)\n"
	@echo

.PHONY: all clean fclean re bonus
