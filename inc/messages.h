#ifndef MESSAGES_H
# define MESSAGES_H

// SYNtax error messages
# define SYN_ERR_EMPTY "minishell: syntax error: command cannot be empty\n"
# define SYN_ERR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define SYN_ERR_REDIRECT "minishell: syntax error near unexpected token `>'\n"
# define SYN_ERR_NL "minishell: syntax error near unexpected token `newline'\n"


# define ERR_CMD_NOT_FOUND ": command not found\n"
# define ERR_NO_FILE "minishell: no such file or directory\n"

# endif