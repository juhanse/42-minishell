# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 01:50:05 by juhanse           #+#    #+#              #
#    Updated: 2025/05/16 01:50:45 by juhanse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -I/opt/homebrew/opt/readline/include
RM = rm -rf

#Directories
SRCDIR = srcs/
OBJDIR = objs/
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

#Sources and objects
PARSING = parsing/clean_memory.c parsing/cmds.c parsing/expand_utils.c parsing/expand.c parsing/free.c parsing/init.c parsing/list_utils.c parsing/syntax.c parsing/tokenize.c parsing/utils.c parsing/valid_input.c parsing/init_env.c parsing/token_utils.c
BUILTINS = builtins/builtins.c builtins/pwd.c builtins/echo.c builtins/env.c builtins/cd.c builtins/unset.c builtins/export.c builtins/exit.c builtins/env_utils.c builtins/export_utils.c
EXEC = execution/executor.c execution/find_command.c execution/pipeline.c execution/redirections.c execution/heredoc.c execution/utils.c
SIGNALS = signals/signals.c
DEBUG = debug/debug.c debug/utils.c
SRC = main.c $(PARSING) $(BUILTINS) $(EXEC) $(SIGNALS) $(DEBUG)

SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

#Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFTDIR) -L/opt/homebrew/opt/readline/lib -lft -lreadline

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(LIBFTDIR) -c $< -o $@

#Libft compilation
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	$(RM) $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
