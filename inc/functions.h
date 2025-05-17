/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:14:09 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/17 13:22:49 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* Init Shell */
int		init_shell(t_shell **shell);
t_cmd	*create_cmd(void);

/* Tokens */
t_tkn	*tokenize_input(char *line);
t_tkn	*read_operator(char **str);
t_tkn	*read_token(char **str);

/* Utils */
void	error_exit(const char *msg, int exit_code);
void	free_data(t_shell *shell);
void	ft_free_tokens(t_tkn *tokens);
//void	ft_free_list(t_cmd *cmd);
void	ft_free_parts(t_tkn_part *parts);
int		clean_exit(t_shell *shell, int status);
void	free_redirect_list(t_redir *redir);
void	free_env_list(t_env *env);
void	free_cmd_list(t_cmd *cmd);
//void	change_env_variable(t_env *env, char *key, char *value);
//char	*get_env_variable_value(t_env *env, char *key);

/* Parser */
//int		count_envp(t_env *env);
void	expand_variable(t_shell *shell);
bool	validate_token_syntax(t_tkn *tokens);
bool	is_redirect(t_tkn_type type);
char	*expand_var_value(char *value, t_shell *shell);
//void	handle_envp_count(int *i, t_env *env);
//void	handle_pid(int *i);
char	**append_arg(char **args, char *arg);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
//char	*ft_strjoin_free(char *s1, const char *s2);
//char	*ft_strjoin_char(char *s, char c);
t_redir	*create_redir(t_tkn *tkn);
void	add_redir_to_list(t_redir **list, t_redir *new_redir);
void	handle_redirect(t_redir **redir_list, t_tkn **tkn);
//char	*handle_exit_status(int exit_status);
char	*handle_env_variable(char *value, int *i, t_env *env);
char	*handle_dollar_sign(char *value, int *i, t_shell *shell);
char	*append_doll_and_char(char *expanded, char next_char);
int		validate_syntax(t_cmd *cmd_list);
void	add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd);
char	*join_token_parts(t_tkn_part *parts);
bool	handle_pipe(t_cmd **cmd_list, t_cmd **current_cmd, t_tkn **tokens);
bool	handle_redirect_wrapper(t_cmd *cmd, t_tkn **tokens);

/* Signals */
void	set_signals(void);

/* Pipe */
//int		execute_cmds(t_cmd *cmds, t_env *env);
void	handle_heredoc(t_cmd *cmd, t_shell *shell);
void	execute_piped_commands(t_cmd *cmd_list, t_shell *shell);
int		handle_redirections(t_cmd *cmd);
//void	init_pipe_data(t_pipe *pdata, t_cmd *cmds);
//void	close_unused_fds(t_pipe *pdata);
//int		wait_all(t_pipe *pdata);
//void	free_pipe_data(t_pipe *pdata);
//int		count_cmds(t_cmd *cmd);
//int		execute_single_command(t_cmd *cmd, t_env *env);

/* Commands */
void	execute_commands(t_cmd *cmds, t_shell *shell, char *line);
t_cmd	*parse_tokens(t_tkn *tokens);
int		ft_echo(t_cmd *cmd);
int		setup_environment(t_shell *shell, char **envp);
int		ft_env(t_env *env_list);
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

/* Else */
//void	skip_delimiters(char **str);
//void	builtin_error(char *cmd, char *arg, char *msg);
char	*safe_strdup(const char *str);
int		exec_cmd(char *cmd, char **args, t_env *env);
void	clean_array(char **array);
int		is_builtin_command(char *cmd);

/* Execute */
char	*find_command_path(char *cmd, t_env *env);
char	**env_to_array(t_env *env);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	handle_commands(char *line, t_shell *shell);

#endif
