/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:25:47 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/07 12:46:08 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TYPES_H
# define SHELL_TYPES_H

# ifndef SHELL_CONTINUE 
#  define SHELL_CONTINUE 0
# endif
# ifndef SHELL_EXIT 
#  define SHELL_EXIT 1
# endif

typedef enum e_pos
{
	HEAD,
	TAIL,
}	t_pos;

/*  ==========================
    === TOKENIZER & PARSER ===
    ========================== */

typedef enum e_tkn_type
{
	TOK_WORD,
	TOK_OPERATOR,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_APPEND,
	TOK_HEREDOC,
}	t_tkn_type;

typedef struct s_tkn
{
	char				*value; // Valor del token (ej: "echo", ">", "file.txt")
	t_tkn_type			type; // Tipo de token (WORD, OPERATOR, etc.)
	bool				s_quote;
	bool				db_quote;
	struct s_tkn		*next; // Siguiente token en la lista
}	t_tkn;

/*  =====================
    === REDIRECCTIONS ===
    ===================== */

typedef enum e_redir_type
{
	REDIR_IN, // <
	REDIR_OUT, // >
	REDIR_APPEND, // >>
	REDIR_HEREDOC, // <<
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type			type; // Tipo de redirección (<, >, <<, >>)
	char					*file;// Archivo asociado a la redirección
	int						fd;// File descriptor
	char					*delimiter;
	struct s_redir			*next;// Siguiente redirección en la lista
}	t_redir;

/*  ================
    === COMMANDS ===
    ================ */

typedef struct s_cmd
{
	char				*cmd; // Comando a ejecutar (ej: "echo")
	char				**args; // Argumentos del comando (ej: {"-n", "Hola"})
	t_redir				*redirs; // Lista de redirecciones
	struct s_cmd		*next;// Siguiente comando en la lista
}	t_cmd;

/*  =========================
    === PIPES / EJECUTION ===
    ========================= */

typedef struct s_pipe
{
	int		fd[2]; //Pipe actual
	int		prev_fd;//Pipe anterior para el proximo hjo
	pid_t	*pids; // Array de pids de hijos
	int		n_cmds; // Cantidad de comandos
}	t_pipe;

/*  ====================
    === ENVIRONMENT  ===
    ==================== */

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

/*  ====================
	=== MOTHER SHELL ===
	==================== */

typedef struct s_shell
{
	t_env				*env;// Variables de entorno
	t_tkn				*tkns;// Lista de tokens (para parsing)
	t_cmd				*cmds;// Lista de comandos a ejecutar
	int					exit_status;// Estado de salida del último comando
	char				*cur_dir;// Directorio actual
}	t_shell;

#endif
