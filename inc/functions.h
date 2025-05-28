/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:14:09 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 14:02:16 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* ========================================================================= */
/*                                Init Shell                                 */
/* ========================================================================= */
int		init_shell(t_shell **shell);
int		setup_environment(t_shell *shell, char **envp);
t_cmd	*create_cmd(void);

/* ========================================================================= */
/*                               Tokenizer                                   */
/* ========================================================================= */
t_tkn	*prepare_tokens(char *line, t_shell *shell);
t_tkn	*tokenize_input(char *line, t_shell *shell);
t_tkn	*read_operator(char **stri, t_shell *shell);
t_tkn	*read_token(char **stri, t_shell *shell);
char	*join_token_parts(t_tkn_part *parts);

/* ========================================================================= */
/*                                Parser                                     */
/* ========================================================================= */
t_cmd	*check_and_parse(t_tkn *tokens, t_shell *shell);
t_cmd	*parse_tokens(t_tkn *tokens, t_shell *shell);
bool	validate_token_syntax(t_tkn *tokens, t_shell *shell);
int		validate_syntax(t_cmd *cmd_list, t_shell *shell);
bool	is_redirect(t_tkn_type type);
bool	is_empty_quoted_var(const char *value, int i);
bool	handl_pipe(t_cmd **cmd_lst, t_cmd **cur_cmd, t_tkn **tkns, t_shell *sh);
bool	handle_redirect_wrapper(t_cmd *cmd, t_tkn **tokens, t_shell *shell);
void	handle_redirect(t_redir **redir_list, t_tkn **tkn);
void	add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
void	add_redir_to_list(t_redir **list, t_redir *new_redir);
t_redir	*create_redir(t_tkn *tkn);
char	**append_arg(char **args, char *arg);

/* ========================================================================= */
/*                            Variable Expansion                             */
/* ========================================================================= */
void	expand_variable(t_shell *shell);
char	*expand_var_value(char *value, t_shell *shell);
char	*handle_env_variable(char *value, int *i, t_env *env);
char	*handle_dollar_sign(char *value, int *i, t_shell *shell);
char	*append_doll_and_char(char *expanded, char next_char);

/* ========================================================================= */
/*                              Execution                                    */
/* ========================================================================= */
void	handle_commands(char *line, t_shell *shell);
void	execute_commands(t_cmd *cmds, t_shell *shell, char *line);
void	execute_single_command(t_cmd *cmd, t_shell *shell, char *line);
int		handle_external_command(t_cmd *cmd, t_shell *shell);
int		handle_redirections(t_cmd *cmd);
int		handle_redir_only_command(t_cmd *cmd, t_shell *shell);
int		exec_cmd(char *cmd, char **args, t_env *env);
int		validate_cmd(char *cmd_path);
char	*check_cmd_path(char *cmd, t_env *env);
int		check_dot_dot_cmd(char *cmd);
char	*find_command_path(char *cmd, t_env *env);
int		is_directory(const char *path);
char	**env_to_array(t_env *env);
char	*ft_strjoin3(char *s1, char *s2, char *s3);

/* ========================================================================= */
/*                                 Pipes                                     */
/* ========================================================================= */
void	execute_piped_commands(t_cmd *cmd_list, t_shell *shell);
void	handle_heredoc(t_cmd *cmd, t_shell *shell);
void	wait_for_all(pid_t *pids, int n, t_shell *shell);
void	close_pip_and_wait(int *pipefd, t_redir *redir, t_shell *sh, pid_t pid);

/* ========================================================================= */
/*                              Builtins                                     */
/* ========================================================================= */
int		ft_echo(t_cmd *cmd);
int		ft_pwd(void);
int		ft_cd(t_cmd *cmd, t_shell *shell);
int		ft_env(t_env *env_list);
int		ft_export(t_env **env, t_cmd *cmd);
int		ft_unset(t_cmd *cmd, t_shell *shell);
void	ft_exit(t_cmd *cmd, t_shell *shell);
int		is_builtin_command(char *cmd);
int		handle_builtin_commands(t_cmd *cmd, t_shell *shell, char *line);
void	print_export_list(t_env *env);
void	update_or_append_env(t_env **env, const char *key, const char *value);
void	append_to_env(t_env **env, const char *key, const char *value);
int		is_valid_identifier(const char *key);

/* ========================================================================= */
/*                             Environment                                   */
/* ========================================================================= */
t_env	*create_env_kv(const char *key, const char *value);
void	add_env_node(t_env **head, t_env *new_node);
t_env	*find_env(t_env *env_list, const char *key);
char	*ft_getenv(const char *name, t_env *env);

/* ========================================================================= */
/*                               Signals                                     */
/* ========================================================================= */
void	set_signals(void);
void	reset_signals(void);

/* ========================================================================= */
/*                                Utils                                      */
/* ========================================================================= */
void	restore_stdio(int stdin_backup, int stdout_backup);
char	*safe_strdup(const char *str);
void	clean_array(char **array);
void	error_exit(const char *msg, int exit_code);
char	*get_token_name(t_tkn_type type);
bool	syntax_error(t_shell *shell, const char *msg, t_tkn_type type);

/* ========================================================================= */
/*                                Free                                       */
/* ========================================================================= */
void	free_data(t_shell *shell);
void	ft_free_tokens(t_tkn *tokens);
void	ft_free_parts(t_tkn_part *parts);
void	free_redirect_list(t_redir *redir);
void	free_cmd_list(t_cmd *cmd);
void	free_env_list(t_env *env);
int		clean_exit(t_shell *shell, int status);

#endif
