/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:14:09 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/27 17:57:48 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//Init Shell
t_shell	*init_shell(void);
t_cmd	*create_cmd(void);
//Tokens
t_tkn	*tokenize_input(char *line);
t_tkn	*create_token(char *value, t_tkn_type type);
char	*handle_quotes(char *str, t_tkn *token);
char	*process_non_quotes(char *str);
void	add_token_to_list(t_tkn **tkn, t_tkn *new_tkn, char *start, char *end);
char	*read_token_segment(char **str, bool *s_quote, bool *db_quote);
//Lexer
void	lex_tokens(t_tkn *tkn);
//Utils
void	error_exit(const char *msg, int exit_code);
void	free_data(t_shell *shell);
void	ft_free_tokens(t_tkn *tokens);
void	ft_free_list(t_cmd *cmd);
void	free_redirect_list(t_redir *redir);
void	free_env_list(t_env *env);
void	ft_free_cmd_list(t_cmd *cmd);
void	change_env_variable(t_env *env, char *key, char *value);
char	*get_env_variable_value(t_env *env, char *key);
//Parser
int		count_envp(t_env *env);
void	expand_variable(t_shell *shell);
void	process_input(const char *input, t_shell *shell);
void	handle_envp_count(int *i, t_env *env);
void	handle_pid(int *i);
char	**append_arg(char **args, char *arg);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
char	*ft_strjoin_free(char *s1, const char *s2);
char	*ft_strjoin_char(char *s, char c);
t_redir	*create_redir(t_tkn *tkn);
void	add_redir_to_list(t_redir **list, t_redir *new_redir);
void	handle_redirect(t_redir **redir_list, t_tkn **tkn);
char	*handle_exit_status(int exit_status);
char	*handle_env_variable(char *value, int *i, t_env *env);
char	*handle_dollar_sign(char *value, int *i, t_shell *shell);
char	*append_doll_and_char(char *expanded, char next_char);
//Signals
void	handle_signal(int sig, siginfo_t *info, void *context);
//Pipe
void	execute_child(t_cmd *cmd, t_pipe *pdata, int index, t_env *env);
int		execute_cmds(t_cmd *cmds, t_env *env);
int		handle_heredoc(char *delimiter);
int		execute_piped_commands(t_cmd *cmds, t_pipe *pdata, t_env *env);
int		handle_redirections(t_redir *redir);
void	init_pipe_data(t_pipe *pdata, t_cmd *cmds);
void	close_unused_fds(t_pipe *pdata);
int		wait_all(t_pipe *pdata);
void	free_pipe_data(t_pipe *pdata);
int		count_cmds(t_cmd *cmd);
int		execute_single_command(t_cmd *cmd, t_env *env);
//Commands
void	execute_commands(t_cmd *cmds, t_shell *shell, char *line);
t_cmd	*parse_tokens(t_tkn *tokens);
void	ft_echo(t_cmd *cmd);
t_env	*convert_env(char **envp);
void	ft_env(t_env *env_list);
char	*ft_getenv(const char *name, t_env *env);
void	ft_exit(t_cmd *cmd, t_shell *shell);
void	ft_cd(t_cmd *cmd, t_shell *shell);
void	handle_builtin_commands(t_cmd *cmd, t_shell *shell, char *line);
void	ft_unset(t_cmd *cmd, t_shell *shell);
void	handle_external_command(t_cmd *cmd, t_shell *shell);
void	ft_export(t_env **env, t_cmd *cmd);
void	update_or_append_env(t_env **env, const char *key, const char *value);
t_env	*find_env(t_env *env_list, const char *key);
int		is_valid_identifier(const char *key);
int		is_valid_identifier_export(const char *key);
void	append_to_env(t_env **env, const char *key, const char *value);
// Else
void	skip_delimiters(char **str);
void	builtin_error(char *cmd, char *arg, char *msg);
char	*safe_strdup(const char *str);
int		exec_cmd(char *cmd, char **args, t_env *env);;
void	clean_array(char **array);
void	ft_pwd(void);
//Execute
char	*find_command_path(char *cmd, t_env *env);
char	**env_to_array(t_env *env);
char	*ft_strjoin3(char *s1, char *s2, char *s3);

#endif
