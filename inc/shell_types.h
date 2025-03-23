/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:25:47 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/23 15:44:02 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TYPES_H
# define SHELL_TYPES_H

typedef enum e_pos
{
	HEAD,
	TAIL,
}	t_pos;

/* Tokens */
typedef enum e_tkn_type
{
	TOKEN_UNSET,
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
}	t_tkn_type;

typedef enum e_opertype
{
	OP_UNSET,
	OP_LESS, // <
	OP_GREAT,// >
	OP_DLESS,// <<
	OP_DGREAT,// >>
	OP_PIPE, // |
}	t_opertype;

typedef struct s_tkn
{
	char				*value; // Valor del token (ej: "echo", ">", "file.txt")
	t_tkn_type			type; // Tipo de token (WORD, OPERATOR, etc.)
	bool				terminated; // Indica si el token está terminado
	struct s_tkn		*next; // Siguiente token en la lista
}	t_tkn;

/* Commands & Redirections */
typedef struct s_redirect
{
	t_opertype			type; // Tipo de redirección (<, >, <<, >>)
	char				*file;// Archivo asociado a la redirección
	int					fd;// File descriptor
	struct s_redirect	*next;// Siguiente redirección en la lista
}	t_redirect;

typedef struct s_cmd
{
	char				*cmd; // Comando a ejecutar (ej: "echo")
	char				**args; // Argumentos del comando (ej: {"-n", "Hola"})
	t_redirect			*redirect; // Lista de redirecciones
	bool				is_pipe; // Indica si hay un pipe después de este comand
	int					pipe_fds[2]; // File descriptors para pipes
	pid_t				pid;// PID del proceso hijo
	struct s_cmd		*next;// Siguiente comando en la lista
}	t_cmd;

/* Enviroment */
typedef struct s_env
{
	char				*key;// Nombre de la variable (ej: "PATH")
	char				*value;// Valor de la variable (ej: "/usr/bin")
	struct s_env		*next;// Siguiente variable en la lista
}	t_env;

/* Shell */
typedef struct s_shell
{
	t_env				*env;// Variables de entorno
	t_tkn				*tkns;// Lista de tokens (para parsing)
	t_cmd				*cmds;// Lista de comandos a ejecutar
	int					exit_status;// Estado de salida del último comando
	char				*cur_dir;// Directorio actual
}	t_shell;

#endif
