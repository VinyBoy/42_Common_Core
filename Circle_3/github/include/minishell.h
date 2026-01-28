/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:15:14 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 19:08:20 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define GREEN "\001\033[1;32m\002"
# define RESET "\001\033[0m\002"
# define MALLOC 1
# define FREE 2
# define FREEALL 3
# define S_E "minishell: syntax error near unexpected token"
# define CH "chdir: error retrieving current directory: "
# define CWD "getcwd: cannot access parent directories: "

extern int				g_signal_status;

typedef enum e_tokens
{
	WORD,
	PIPE,
	LESS,
	GREAT,
	LESS_LESS,
	LESS_LESS_LESS,
	GREAT_GREAT,
}						t_tokens;

typedef struct s_token
{
	char				*value;
	t_tokens			type;
	struct s_token		*next;
}						t_token;

typedef struct s_redirs
{
	t_tokens			type;
	char				*file;
	struct s_redirs		*next;
}						t_redirs;

typedef struct s_cmd
{
	char				**args;
	t_redirs			*redirs;
	int					is_pipe;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_node
{
	void				*ptr;
	struct s_node		*next;
}						t_node;

typedef struct t_env
{
	char				*env_var;
	struct t_env		*next;
}						t_env;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}						t_redir_type;

typedef struct s_redir_op
{
	t_redir_type		type;
	char				*target;
	int					here_doc_index;
	struct s_redir_op	*next;
}						t_redir_op;

typedef struct s_redir
{
	t_redir_op			*ops;
	int					final_in_fd;
	int					final_out_fd;
}						t_redir;

typedef struct s_exec
{
	char				**line;
	char				**path;
	char				**envp;
	pid_t				pid;
	pid_t				*pids;
	int					**pipe_fds;
	int					cmd_count;
	int					no_path;
	t_redir				**redir;
}						t_exec;

typedef struct s_here_doc
{
	char				*delim;
	int					pipefd[2];
}						t_here_doc;

typedef struct s_data
{
	int					status;
	int					count;
	int					here_count;
	int					i;
	char				*input;
	t_env				*env;
	t_here_doc			*here;
	t_redir_op			*redir;
}						t_data;

/* Parsing */

/* env.c */
char					*ft_get_env_var(t_env *env, char *var);
t_env					*get_env(char **envp);
void					copy_env(char **envp, t_env **env_copy);
void					add_env_node(t_env **lst, char *line_envp);
t_env					*ft_last_env_node(t_env *node);

/* is_redir_token.c */
int						is_redir_in(t_tokens t);
int						is_redir_out(t_tokens t);
int						is_heredoc(t_tokens t);
int						is_append(t_tokens t);
int						is_redirection_token(t_tokens t);

/* lexer_1.c */
t_token					*ft_lexer(const char *input, int i);
t_token					*convert_word_to_token(char *word);
int						calculate_word_length(const char *input, int start_pos);
int						should_break_on_delimiter(const char *input, int pos,
							int quote_state);
char					*redir_word(const char *input, char *word, int *i,
							int *j);

/* lexer_2.c */
char					find_flag(int in_quote);
int						len_word(const char *input, int *i, char flag_quote);
int						is_redirection(const char *input, int *i);
int						count_redir(const char *input, int *i);
int						len_word_quote(const char *input, int j,
							char flag_quote);

/* lexer_3.c */
int						handle_special_cases(const char *input, int *i);
char					*create_pipe_word(const char *input, int *i);
char					*create_redir_word(const char *input, int *i);
char					*extract_normal_word(const char *input, int *i,
							int word_len);
char					*analyse_and_fill_word(const char *input, int *i);

/* lexer_syntax_error.c */
int						check_condition_token(int *count, t_token *cur);
int						check_redir_error(t_token *cur);
int						check_pipe_error(t_token *lexer);
int						check_syntax_error_lexer(t_token *lexer);
int						is_error_syntax(const char *input);

/* lexer_utils.c */
void					print_lexer(t_token **head);
char					*print_token(t_tokens token);
void					add_token(t_token **head, t_token *tk);
int						update_quote_state(char c, int current_state);

/* new_expand_1.c */
char					*do_expand(char *input, t_data *data);
int						update_quotes(char c, int *in_quote);
int						is_valid_var_start(char c);
int						var_name_len(const char *s);

/* new_expand_2.c */
int						expand_from_dollar(char *new_input, char *input,
							t_data *data, int *j);
int						expand_pid(char *new_input, int *j);
int						expand_exit_status(char *new_input, char *input, int *j,
							t_data *data);
char					*ft_copy_var_name(const char *input, int i);
int						expand_var_env(char *new_input, char *input,
							t_data *data, int *j);

/* new_expand3.c */
int						handle_dollar_double_quote(char *new_input, char *input,
							t_data *data, int *j);
int						handle_dollar_single_quote(char *new_input, char *input,
							t_data *data, int *j);
int						check_dollar(char *input);

/* parsing.c */
t_cmd					*new_parsing(t_data *data);
int						nb_of_pipe(char *input);
void					init_cmd(t_cmd *cmd, int len);

/* print_lexer.c */
void					print_redirs(t_redirs *r);
void					print_args(char **args);
void					print_cmds(t_cmd *cmd);

/* quotes.c */
int						verif_quote(char *input);
int						extract_quotes(char *new_input, char *input, int *i,
							int *j);
char					*clean_quotes(char *input);

/* token_utils.c */
t_tokens				get_token(char *str);
t_tokens				find_type(char *word);
int						len_of_args(char **args);
const char				*redir_type_name(t_tokens type);
void					return_error_double_pipe(void);

/* token_utils_1.c */
int						count_tokens(char *str);
char					*extract_token(char *src, int start, int end);
int						fill_tokens(char **tokens, char *str, int count);
char					**split_expanded_value(char *expanded_str);
int						count_tokens_append(char **tokens);

/* token_utils_2.c */
int						find_variable_end_brace(const char *value, int start);
int						find_variable_end_normal(const char *value, int start);
int						check_double_quote_protection(const char *value, int i);
int						process_dollar_sign(const char *value, int i);
int						token_contains_unprotected_expansion(const char *value);

/* token.c */
void					fill_cmd(t_data *data, t_cmd *cmd, t_token *lexer);
void					add_redir(t_redirs **head, t_redirs *new);
t_redirs				*new_redir(t_tokens type, char *file);
t_cmd					*new_cmd_node(void);
void					append_arg(t_cmd *cmd, char *value, t_data *data);

/* token_1.c */
char					**create_new_args_array(int original_count,
							int additional_count);
void					copy_original_args(char **dest, char **src, int count);
void					copy_tokens(char **dest, char **src, int start_pos,
							int count);
char					**handle_unquoted_variables(t_cmd *cmd,
							char *expanded_value);
char					**handle_normal_case(t_cmd *cmd, char *expanded_value);

/* token_2.c */
char					**handle_split_tokens(t_cmd *cmd, char **split_tokens);
char					**handle_single_token(t_cmd *cmd, char *expanded);
int						check_if_fully_quoted(char *value);
char					*process_quoted_value(char *expanded_value);
char					**other_tokens(char *value, char *expanded_value,
							t_cmd *cmd);

/* Utils */

/* export_utils.c */
int						check_export_event_option(char **strs, t_data *data);
int						is_valid_export_key(const char *str);

/* free.c */
void					free_env_list(t_env *env);
void					free_split(char **strs);
void					free_data(t_data *data);

/* ft_dprintf.c */
int						ft_dprintf(int fd, const char *str, ...);

/* ft_split_mem.c */
char					**ft_split_mem(char const *s, char c);

/* libft_mem.c */
char					*ft_strdup_mem(const char *source);
char					*ft_strjoin_mem(char *s1, char *s2);
char					*ft_itoa_mem(int n);
char					*ft_substr_mem(char const *s, unsigned int start,
							size_t len);

/* mem_manager.c */
void					*mem_manager(int mode, size_t size, void *ptr);

/* signal.c */
void					handle_ctrl_c(int sig);
void					init_signals(void);
void					sig_int_child(int sig);
void					sig_quit_child(int sig);
void					handle_ctrl_d(t_data *data, int *exit_status);

/* utils.c */
void					print_minishell(void);
void					write_error(char *str);
int						count_args(char **strs);
int						count_env(t_env *env);
char					*ft_strncpy(char *dst, const char *src, size_t n);

/* Builtin */
int						is_builtin(char *str);
void					ft_builtin(t_exec *exec, t_data *data, int stdin_save,
							int stdout_save);
void					ft_cd(char **strs, t_data *data);
void					ft_unset(char **strs, t_data *data);
void					ft_pwd(char **strs, t_data *data);
void					export(char *str, t_env **env);
void					ft_export(char **strs, t_data *data);
void					ft_exit(t_exec *exec, t_data *data);
void					ft_env(t_env *env, t_data *data);
void					ft_echo(char **strs, t_data *data);

/* Exec */

/* exec.c */
void					run_exec(t_exec *exec, t_data *data, char *cmd_path);
void					exec_cmd(t_exec *exec, t_data *data, int cmd_index,
							t_cmd *cmd);
int						handle_commands(t_exec *exec, t_data *data, t_cmd *cmd);
int						ft_exec(t_data *data, t_cmd *cmd);

/* exec2.c */
char					*get_cmd_path(t_exec *exec);
int						check_path_permissions(char *cmd_path);
int						handle_cmd_error(char *cmd_path, t_exec *exec);
int						handle_builtin(t_exec *exec, t_data *data);
void					close_pipes(t_exec *exec);

/* exec3.c */
int						handle_single_builtin(t_exec *exec, t_data *data,
							t_cmd *cmd);
int						exec_env(t_exec *exec, t_data *data);
int						create_pipes(t_exec *exec);
int						pids_alloc(t_exec *exec);
void					setup_pipes(t_data *data, t_exec *exec, int cmd_index);

/* exec4.c */
int						create_child_processes(t_exec *exec, t_data *data,
							t_cmd *cmd);
void					close_heredoc_pipes(t_data *data);
t_cmd					*find_current_cmd(t_cmd *cmd, int cmd_index);
void					validate_cmd_args(t_cmd *current, t_exec *exec);
void					execute_external_cmd(t_exec *exec, t_data *data);

/* free_exec.c */
void					free_exec(t_exec *exec);
void					free_single_redir(t_redir *redir);
void					free_redirections(t_exec *exec);
void					free_pipes(t_exec *exec);
void					handle_signals_in_child(void);

/* exec_wait.c */
int						wait_for_children(t_exec *exec);

/* exec_utils.c */
void					init_exec(t_exec *exec);
char					**env_to_array(t_env *env);
void					write_join_error(char *s1, char *s2, char *s3);
void					dup_pipe_end(t_data *data, int old_fd, int new_fd,
							t_exec *exec);
int						count_cmds(t_cmd *cmd);

/* exec_redir.c */
int						is_redir(char c);
int						handle_redir_out(t_redir_op *op, int *current_out_fd);
int						process_single_redir(t_redir_op *op, t_data *data,
							int *in_fd, int *out_fd);
int						process_all_redirs(t_redir *redir, t_data *data,
							int *in_fd, int *out_fd);
int						setup_redir(t_redir *redir, t_data *data);

/* exec_redir2.c */
int						alloc_redir(t_exec *exec, t_cmd *cmd);
int						process_cmd_redir(t_exec *exec, t_cmd *cmd);
void					apply_redir(t_exec *exec, t_data *data, int cmd_index);
void					close_redir(t_redir *redir);
void					close_all_redir(t_exec *exec);

/* exec_redir3.c */
t_redir_type			op_type(t_tokens type);
t_redir_op				*redirs_to_ops(t_redirs *redirs);
void					init_cmd_redir(t_redir *redir, t_cmd *cmd, int i);

/* exec_redir4.c */
void					close_fd_if_valid(int fd);
void					set_error_state(t_redir *redir);
int						handle_redir_in(t_redir_op *op, int *current_in_fd);
int						handle_heredoc(t_redir_op *op, t_data *data,
							int *current_in_fd);
int						get_output_flags(int redir_type);

/* exec_redir5.c */
int						setup_stdin_redirect(int final_in_fd);
int						setup_stdout_redirect(int final_out_fd);
void					handle_builtin_redir(t_exec *exec, t_data *data);
char					**line_clean(char **line);

/* Here_doc */

/* here_doc.c */
void					init_here_doc(t_data *data);
int						count_here_doc(t_exec *exec);
int						allocate_here_doc(t_data *data, int count);
int						is_quoted_delim(char *delim);

/* here_doc2.c */
int						setup_here_doc(t_exec *exec, t_data *data);
int						find_here_doc_index(t_data *data, char *delim);
void					close_here_doc(t_data *data);

/* here_doc3.c */
int						process_single_here_doc(t_data *data, char *delim,
							int index);

/* expand_here.c */
char					*do_expand_here(char *input, t_data *data);

/* here_doc_child.c */
void					handle_here_doc_child(char *delim, int pipefd[2],
							t_data *data);

/* here_doc_signals.c */
void					ctrl_d_here_doc(char *line, char *delim, t_data *data);
void					sig_int_here_doc(int sig);

#endif