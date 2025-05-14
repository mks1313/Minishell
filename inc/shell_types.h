/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:25:47 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/14 16:20:05 by mmarinov         ###   ########.fr       */
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
	TOK_EOF,
}	t_tkn_type;

typedef enum e_tkn_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE,
	Q_MIX
}	t_tkn_quote;

typedef struct s_tkn_part
{
	char				*value;
	t_tkn_quote			quote;
	struct s_tkn_part	*next;
}	t_tkn_part;

typedef struct s_tkn
{
	t_tkn_type		type;
	t_tkn_part		*parts;
	struct s_tkn	*next;
}	t_tkn;

/*  =====================
    === REDIRECCTIONS ===
    ===================== */

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	int					fd;
	char				*delimiter;
	t_tkn_quote			delim_quote;
	struct s_redir		*next;
}	t_redir;

/*  ================
    === COMMANDS ===
    ================ */

typedef struct s_cmd
{
	char				*cmd;
	char				**args;
	t_redir				*redirs;
	struct s_cmd		*next;
}	t_cmd;

/*  =========================
    === PIPES / EJECUTION ===
    ========================= */

typedef struct s_pipe
{
	int					fd[2];
	int					prev_fd;
	pid_t				*pids;
	int					n_cmds;
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
	t_env				*env;
	t_tkn				*tkns;
	t_cmd				*cmds;
	int					exit_status;
}	t_shell;

#endif
