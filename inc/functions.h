/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:14:09 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/20 19:30:54 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* Init Shell */
int		init_shell(t_shell **shell);
t_cmd	*create_cmd(void);

/* Tokens */
t_tkn	*tokenize_input(char *line, t_shell *shell);
t_tkn	*read_operator(char **stri, t_shell *shell);
t_tkn	*read_token(char **stri, t_shell *shell);

/* Parser */
void	expand_variable(t_shell *shell);
bool	validate_token_syntax(t_tkn *tokens, t_shell *shell);
bool	is_redirect(t_tkn_type type);
t_cmd	*parse_tokens(t_tkn *tokens, t_shell *shell);
char	*expand_var_value(char *value, t_shell *shell);
char	**append_arg(char **args, char *arg);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
t_redir	*create_redir(t_tkn *tkn);
bool	is_empty_quoted_var(const char *value, int i);
void	add_redir_to_list(t_redir **list, t_redir *new_redir);
void	handle_redirect(t_redir **redir_list, t_tkn **tkn);
char	*handle_env_variable(char *value, int *i, t_env *env);
char	*handle_dollar_sign(char *value, int *i, t_shell *shell);
char	*append_doll_and_char(char *expanded, char next_char);
int		validate_syntax(t_cmd *cmd_list, t_shell *shell);
void	add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd);
char	*join_token_parts(t_tkn_part *parts);
bool	handl_pipe(t_cmd **cmd_lst, t_cmd **cur_cmd, t_tkn **tkns, t_shell *sh);
bool	handle_redirect_wrapper(t_cmd *cmd, t_tkn **tokens, t_shell *shell);

/* Signals */
void	set_signals(void);
void	reset_signals(void);

/* Pipe */
void	handle_heredoc(t_cmd *cmd, t_shell *shell);
void	execute_piped_commands(t_cmd *cmd_list, t_shell *shell);
int		handle_redirections(t_cmd *cmd);
void	wait_for_all(pid_t *pids, int n, t_shell *shell);
void	close_pip_and_wait(int *pipefd, t_redir *redir, t_shell *sh, pid_t pid);

/* Commands */
void	execute_commands(t_cmd *cmds, t_shell *shell, char *line);
int		ft_echo(t_cmd *cmd);
int		setup_environment(t_shell *shell, char **envp);
int		ft_env(t_env *env_list);
t_env	*create_env_kv(const char *key, const char *value);
void	add_env_node(t_env **head, t_env *new_node);
char	*ft_getenv(const char *name, t_env *env);
void	ft_exit(t_cmd *cmd, t_shell *shell);
int		ft_pwd(void);
int		ft_cd(t_cmd *cmd, t_shell *shell);
int		handle_builtin_commands(t_cmd *cmd, t_shell *shell, char *line);
int		ft_unset(t_cmd *cmd, t_shell *shell);
int		handle_external_command(t_cmd *cmd, t_shell *shell);
int		ft_export(t_env **env, t_cmd *cmd);
void	print_export_list(t_env *env);
void	update_or_append_env(t_env **env, const char *key, const char *value);
t_env	*find_env(t_env *env_list, const char *key);
int		is_valid_identifier(const char *key);
void	append_to_env(t_env **env, const char *key, const char *value);

/* Utils */
char	*safe_strdup(const char *str);
int		exec_cmd(char *cmd, char **args, t_env *env);
void	clean_array(char **array);
int		is_builtin_command(char *cmd);
void	error_exit(const char *msg, int exit_code);
char	*get_token_name(t_tkn_type type);
bool	syntax_error(t_shell *shell, const char *msg, t_tkn_type type);
void	free_data(t_shell *shell);
void	ft_free_tokens(t_tkn *tokens);
void	ft_free_parts(t_tkn_part *parts);
int		clean_exit(t_shell *shell, int status);
void	free_redirect_list(t_redir *redir);
void	free_env_list(t_env *env);
void	free_cmd_list(t_cmd *cmd);
int		is_directory(const char *path);

/* Execute */
char	*check_cmd_path(char *cmd, t_env *env);
int		check_dot_dot_cmd(char *cmd);
int		validate_cmd(char *cmd_path);
char	*find_command_path(char *cmd, t_env *env);
char	**env_to_array(t_env *env);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	handle_commands(char *line, t_shell *shell);

#endif
