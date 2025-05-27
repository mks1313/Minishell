/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:23:36 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/27 15:13:56 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

/* ----------------------------- */
/*         SYNTAX ERRORS         */
/* ----------------------------- */
# define SYN_ERR_UNCLOSED_QUOTE "minishell: syntax error: unclosed quote\n"
# define SYN_ERR_EMPTY     "minishell: syntax error: command cannot be empty\n"
# define SYN_ERR_PIPE      "minishell: syntax error near unexpected token `|'\n"
# define SYN_ERR_REDIRECT  "minishell: syntax error near unexpected token `>'\n"
# define SYN_ERR_NL        "minishell: syntax error near unexpected token \
	`newline'\n"
# define SYN_ERR_INVALID_OPERATOR "minishell: syntax error near unexpected \
	token `invalid operator'\n"

/* ----------------------------- */
/*         EXEC ERRORS          */
/* ----------------------------- */
# define ERR_CMD_NOT_FOUND ": command not found\n"
# define ERR_NO_FILE       "minishell: no such file or directory\n"
# define ERR_IS_DIR        ": Is a directory\n"

/* ----------------------------- */
/*         BUILTIN: CD          */
/* ----------------------------- */
# define ERR_CD_NOT_SET    "minishell: cd: HOME not set\n"
# define ERR_CD_PREFIX     "minishell: cd"
# define ERR_CD_RETRIEVE   "minishell: cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n"

/* ----------------------------- */
/*         BUILTIN: EXIT        */
/* ----------------------------- */
# define ERR_EXIT_TOO_MANY_ARGS     "exit: too many arguments\n"
# define ERR_EXIT_NUMERIC_PREFIX    "minishell: exit: "
# define ERR_EXIT_NUMERIC_SUFFIX    ": numeric argument required\n"

/* ----------------------------- */
/*         GENERAL               */
/* ----------------------------- */
# define EXIT_MSG         "exit\n"
# define ERR_SIG          "Error: sigaction.\n"
# define ERR_MEMORY       "Error: memory allocation failed.\n"

#endif
