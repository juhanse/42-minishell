/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:09:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/17 11:06:58 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int	g_exit_code;

# ifndef ECHOCTL
#  define ECHOCTL 0001000
# endif

# define ISSPACE "\t\n\v\f\r "
# define METACHAR "|<> "
# define FAIL 1
# define SUCCESS 0
# define ERR_CMD_NF "minishell: %s: command not found\n"
# define ERR_MALLOC "minishell: malloc failed."
# define ERR_SUCH_FOD "minishell: %s: No such file or directory\n"
# define ERR_TOK_APP "minishell: syntax error near unexpected token `>>'"
# define ERR_TOK_HD "minishell: syntax error near unexpected token `<<'"
# define ERR_TOK_NL "minishell: syntax error near unexpected token `newline'"
# define ERR_TOK_PIPE "minishell: syntax error near unexpected token `|'"
# define ERR_TOK_RIN "minishell: syntax error near unexpected token `<'"
# define ERR_TOK_ROUT "minishell: syntax error near unexpected token `>'"
# define ERR_EXPORT "minishell: export: `%s': not a valid identifier\n"
# define ERR_OLDPWD "minishell: cd: OLDPWD not set\n"
# define ERR_EXIT_NUM "minishell: exit: %s: numeric argument required\n"
# define ERR_EXIT_ARGS "minishell: exit: too many arguments\n"

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC
}	t_type;

typedef struct s_redir
{
	t_type			type;
	int				fd;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_token
{
	t_type			type;
	char			*value;
	int				in_quote;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char		**env;
	char		*prompt;
	int			cmd_count;
	t_cmd		*cmd_list;
	t_token		*tokens;
}	t_shell;

// PARSING
int		check_expand(t_shell *data, t_token *tokens);
char	*find_env_value(const char *key, char **env, t_shell *data);
void	get_next_quote(t_shell *data, int *j, int *len);
void	init_cmds(t_cmd **current, t_cmd **head, t_shell **data);
void	init_data(t_shell **data, char **envp);
char	**init_env(char **envp, t_shell *data);
int		in_word(char c);
int		is_exp_char(char c);
int		is_redir(t_type type);
void	lst_addback(t_token **lst_head, t_token *new_tok);
int		lst_size(t_token *lst);
t_token	*new_token(int type, char *value, int quote, t_shell *data);
void	print_error(char *error_msg, int exit_status);
int		quote_type(char quote);
char	*remove_quotes(char	*word, t_shell *data);
void	reset_data(t_shell *data);
int		should_expand(const char *value, int quote_status);
char	*strjoin_char(char *res, char c, int *i, t_shell *data);
int		syntax_error(t_token *tokens);
void	tokenize(t_shell *data);
t_cmd	*tokens_to_cmds(t_token *tokens, t_shell *data);
int		valid_input(char *prompt);

//SIGNALS
void	exec_signals(void);
void	ignore_signals(void);
void	init_signals(void);

// BUILTINS
int		export_is_valid(char *str);
char	*export_merge_split(char **args, int i);
char	*export_remove_quotes(t_shell *data, char *s);
int		ft_add_env(t_shell *data, char *name, char *value);
void	ft_builtins(t_shell *data, t_cmd *cmd);
void	ft_cd(t_shell *data, char *path);
char	**ft_copy_env(t_shell *data);
void	ft_echo(char **args);
void	ft_env(t_shell *data, char **args);
void	ft_exit(t_shell *data);
void	ft_export(t_shell *data, int is_export);
char	*ft_getenv(t_shell *data, char *name);
int		ft_isbuiltins(char *cmd);
void	ft_pwd(void);
int		ft_setenv(t_shell *data, char *name, char *value, int overwrite);
void	ft_sort_env(char **env);
void	ft_unset(t_shell *data, char **args);

// EXECUTION
void	apply_redirections(t_redir *redirs);
void	close_pipes(t_shell *data, int **pipes, pid_t last_pid);
void	execute_command(t_shell *data);
void	execute_pipeline(t_shell *data);
void	execute_simple(t_shell *data);
char	*find_command_path(t_shell *data, char *cmd);
void	ft_exec_backup(t_shell *data, int *stdin_backup, int *stdout_backup);
void	ft_exec_restore(int stdin_backup, int stdout_backup);
void	ft_handle_heredocs(t_cmd *cmd);
void	ft_native_cmd(t_shell *data);
void	handle_fork_error(t_shell *data, int **pipes, pid_t last_pid);

// MEMORY
void	*clean_malloc(size_t size, t_shell *data);
char	*clean_strdup(const char *str, t_shell *data);
char	*clean_strjoin(const char *s1, const char *s2, t_shell *data);
char	*clean_substr(char const *s, int start, size_t len, t_shell *data);
void	free_cmds(t_cmd *cmd);
void	free_data(t_shell *data);
void	free_tab(char **tab);
void	free_tokens(t_token *tokens);

// DEBUG
void	print_cmd_list(t_cmd *cmd_list);
void	print_tokens(t_token *token_list);
void	print_tab(char **tab);
void	print_tab_str(char **tab, char *key);

#endif
