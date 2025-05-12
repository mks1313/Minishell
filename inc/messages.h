#ifndef MESSAGES_H
# define MESSAGES_H

// SYNtax error messages
# define SYN_ERR_EMPTY "minishell: syntax error: command cannot be empty\n"
# define SYN_ERR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define SYN_ERR_REDIRECT "minishell: syntax error near unexpected token `>'\n"
# define SYN_ERR_NL "minishell: syntax error near unexpected token `newline'\n"

# define ERR_CMD_NOT_FOUND ": command not found\n"
# define ERR_NO_FILE "minishell: no such file or directory\n"

# define ERR_CD_NOT_SET "minishell: cd: HOME not set\n"
# define ERR_CD "minishell: cd"
# define ERR_RETRIEVING "minishell: cd: error retrieving current directory: \
			getcwd: cannot access parent directories: \
			No such file or directory\n"

# define ERR_EXIT "exit: too many arguments\n"

# define EXIT_MSG			"exit\n"
# define ERR_SIG			"Error: sigaction.\n"
# define ERR_MEMORY			"Error: memory allocation failed.\n"
# define EXIT_SUCCESS_CODE 0
# define EXIT_TOO_MANY_ARGS 1
# define EXIT_NON_NUMERIC_ARG 2

# ifdef DEBUG_MODE

# define LOG_DEBUG(fmt, ...) \
	dprintf(STDERR_FILENO, CYAN"[DEBUG] %s:%d: "RES fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#  define LOG_WARN(fmt, ...) \
	dprintf(STDERR_FILENO, YELL"[WARN]  %s:%d: "RES fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#  define LOG_ERROR(fmt, ...) \
	dprintf(STDERR_FILENO, RED"[ERROR] %s:%d: "RES fmt, __FILE__, __LINE__, ##__VA_ARGS__)

# else

#  define LOG_DEBUG(...) ((void)0)
#  define LOG_WARN(...)  ((void)0)
#  define LOG_ERROR(...) ((void)0)

# endif

# endif
