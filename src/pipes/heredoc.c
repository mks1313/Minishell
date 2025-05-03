/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:12:10 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/03 19:26:18 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void create_heredoc_file(t_redir *redir, t_shell *shell)
{
    char    *line;
    int     fd;
    char    tmp_name[64];

    // Crear un nombre único para el archivo de heredoc
    snprintf(tmp_name, sizeof(tmp_name), "/tmp/.heredoc_%d", getpid());
    fd = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
    {
        perror("heredoc: open");
        return;
    }
    // Asignar el nombre del archivo heredoc a la redirección
    free(redir->file);
    redir->file = ft_strdup(tmp_name);
    // Pedir líneas de entrada hasta que se ingrese el delimitador
    while (1)
    {
        line = readline("> ");  // Solicitar entrada al usuario
        if (!line)  // Si readline falla (ctrl+D o error)
            break;  // Salir si readline falla
        // Si la línea es igual al delimitador, terminamos el heredoc
        if (redir->delimiter && ft_strcmp(line, redir->delimiter) == 0)
        {
            free(line);
            break ;
        }
        // Crear un token temporal para la línea leída
        t_tkn *temp_token = malloc(sizeof(t_tkn));
        temp_token->value = line;
        temp_token->next = NULL;
        temp_token->s_quote = 0; // Aquí se podría agregar la gestión de comillas si es necesario
        // Expandir las variables dentro de la línea
        expand_variable(shell);
        // Expandir las variables en el contenido de la línea si es necesario
        expand_variable(shell);  // Se invoca sobre el shell, que debe manejar la lista de tokens
        // Escribir la línea expandida al archivo de heredoc
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);  // Liberar la memoria de la línea leída
    }
    // Cerrar el archivo de heredoc
    close(fd);
}

/**
 * Iterar sobre los elementos
 * Iterar sobre las redirecciones del comando
 * Si la redirección es un heredoc
 * Llamar a la función para crear el archivo heredoc
 * Avanzar a la siguiente redirección
 * Avanzar al siguiente comando
 */
void	handle_heredoc(t_cmd *cmd, t_shell *shell)
{
	t_redir	*r;

	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == REDIR_HEREDOC)
				create_heredoc_file(r, shell);
			r = r->next;
		}
		cmd = cmd->next;
	}
}
