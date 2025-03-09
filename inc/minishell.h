/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:47:17 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/09 11:57:24 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 * Libraries:
 * signal.h for sigaction()
 * readline for readline()
 * stdlib for exit()
 */
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "sys_includes.h"
# include "shell_types.h"

/* Colors */
# define RESET	"\033[0m"
# define RED	"\033[38;5;203m"
# define GOLD	"\033[38;5;220m"
# define GREEN	"\033[38;5;120m"

/* Errors */
# define EXIT_MSG			"exit\n"
# define ERR_SIG			"Error: sigaction.\n"
# define ERR_MEMORY			"Error: memory allocation failed.\n"
# define EXIT_SUCCESS_CODE 0
# define EXIT_TOO_MANY_ARGS 1
# define EXIT_NON_NUMERIC_ARG 2

/* macros, comandos y builtins */
# define CD			"cd"
# define PWD		"pwd"
# define ENV		"env"
# define EXIT		"exit"
# define EXPORT 	"export"
# define UNSET		"unset"
# define ECHO		"echo"

/* Functions for manage signals*/
void	handle_signal(int sig, siginfo_t *info, void *context);
void	set_sig(struct sigaction *sa, void(*handler)(int, siginfo_t *, void *));
void	handle_sigint(int sig, siginfo_t *info, void *context);
/*Function for manage enviroment variables*/
void	expand_variable(const char *inpt, char **envp, int last_exit_status);
//void	set_env_var(const char *key, const char *value, t_env **env_list);
//void	unset_env_var(cost char *key, t_env **env_list);
//char	*ft_getenv(const char *key, t_env *env_list);
void	handle_double_quotes(const char *inpt, char **envp);
void	handle_single_quotes(const char *input);
void	process_input(const char *input, char **envp);
/*Functions for builtins*/
int		ft_cd(char **cmd, t_data *data);
int		ft_echo(char **cmd);
//int		ft_pwd(char **cmd);
t_env	*convert_env(char **envp);
void	ft_env(t_env *env_list);
int		ft_exit(char **cmd);
//int		ft_export(char **cmd, t_env **env_list);
//int		ft_unset(char **cmd, t_env **env_list);
/*Functions for manage redirections & pipes*/
//int	handle_redirection(t_cmd *cmd);
//int	handle_pipe(t_cmd *cmd, t_data *data);
//int	execute_cmd(t_cmd *cmd, t_data *data);
//int	execute_builtin(t_cmd *cmd, t_data *data);
/*Functions tokenization & parsing*/
//char	**parse_input(char **input);
//t_cmd	*parse_command(char *input, t_data *data);
//void	free_cmd_list(t_cmd *cmd_list);
/*Auxiliar functions*/
void	error_exit(const char *message, int exit_code);
void	del(void *content);
//void	print_prompt(void);
/*Main function for ejecute the shell*/
//void	run_minishell(t_data *data);
//Func init data
t_data	*initialize_data(void);
t_cmd	*create_cmd(void);
void	free_data(t_data *data);

#endif
