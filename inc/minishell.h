/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:47:17 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/05 20:46:41 by mmarinov         ###   ########.fr       */
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
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
//# include "../libft/includes/libft.h"
# include "libft.h"

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

/* Manejo variavbles del entorno*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*Comandos y redirecciones*/
typedef struct s_cmd
{
	char			*command; //Comando a ejecutar
	char			**args; //Argumenots del comando
	char			*input_file;// Archivo de entrada(para redireccion)
	char			*output_file;// Archvo de salida (para redireccion)
	int				append_output;
	bool			pipe;// Si el comando usa tuberia
	int				error_redirect; // Para redirigir el flujo de errores
	bool			heredoc;// Para manejar herencia de entradas
	struct s_cmd	*next;// Para manejar multiples comandos
}	t_cmd;

/*Datos e Shell*/
typedef struct s_data
{
	t_env			*env; //Variables del entorno
	t_cmd			*cmd_list; //Lista de comandos(si ejecuta multimples cmds)
	char			*cur_dir;
	int				status; //Estado de salida del ultimo comando
}	t_data;

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
