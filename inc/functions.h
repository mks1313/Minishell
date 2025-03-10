/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:14:09 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/10 18:53:08 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//Init Shell
t_shell	*init_shell(void);
t_cmd	*create_cmd(void);
//Tokens
t_tkn	*tokenize_input(char *line);
//Utils
void	error_exit(const char *msg, int exit_code);
void	del(void *content);
void	free_data(t_shell *shell);
void	ft_free_tokens(t_tkn *tokens);
//Parser
void	handle_single_quotes(const char *input);
void	handle_double_quotes(const char *inpt, t_env *env);
int		count_envp(t_env *env);
void	expand_variable(const char *input, t_env *env, int last_exit_status);

void	process_input(const char *input, t_env *env);
//Signals
void	handle_signal(int sig, siginfo_t *info, void *context);
//Commands
void	ft_echo(t_tkn *tokens);
t_env	*convert_env(char **envp);
void	ft_env(t_env *env_list);
char	*ft_getenv(const char *name, t_env *env);
int		ft_exit(char **cmd);
void	ft_cd(t_tkn *tokens, t_shell *shell);
// Else
char	*skip_delimiters(char *str, const char *delimiters);

#endif
