/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:09:39 by mmarinov          #+#    #+#             */
/*   Updated: 2025/02/26 13:43:05 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void handle_single_quotes(const char *input) {
    int i = 0;
    while (input[i]) {
        if (input[i] == '\'') {
            i++; // Saltar la comilla de apertura
            while (input[i] && input[i] != '\'') {
                putchar(input[i]);
                i++;
            }
            i++; // Saltar la comilla de cierre
        } else {
            putchar(input[i]);
            i++;
        }
    }
}

void handle_double_quotes(const char *input) {
    int i = 0;
    while (input[i]) {
        if (input[i] == '"') {
            i++; // Saltar la comilla de apertura
            while (input[i] && input[i] != '"') {
                if (input[i] == '$') {
                    i++;
                    // Aquí buscaríamos la variable de entorno, por ejemplo, $USER
                    if (strncmp(&input[i], "USER", 4) == 0) {
                        printf("%s", getenv("USER"));
                        i += 4;
                    }
                } else {
                    putchar(input[i]);
                    i++;
                }
            }
            i++; // Saltar la comilla de cierre
        } else {
            putchar(input[i]);
            i++;
        }
    }
}

void handle_backticks(const char *input) {
    int i = 0;
    while (input[i]) {
        if (input[i] == '`') {
            i++; // Saltar la comilla de apertura
            char cmd[100] = {0};
            int j = 0;
            while (input[i] && input[i] != '`') {
                cmd[j++] = input[i++];
            }
            cmd[j] = '\0';
            i++; // Saltar la comilla de cierre

            // Ejecutar el comando y capturar la salida
            int fd[2];
            pipe(fd);
            if (fork() == 0) {
                // Hijo: ejecuta el comando
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO); // Redirige la salida al pipe
                execlp(cmd, cmd, NULL); // Ejecuta el comando (sin argumentos en este ejemplo)
                exit(1);
            } else {
                // Padre: lee la salida del pipe
                close(fd[1]);
                char buffer[1024];
                int n;
                while ((n = read(fd[0], buffer, sizeof(buffer)-1)) > 0) {
                    buffer[n] = '\0';
                    printf("%s", buffer);
                }
                close(fd[0]);
            }
        } else {
            putchar(input[i]);
            i++;
        }
    }
}

void expand_variable(const char *input) {
    int i = 0;
    while (input[i]) {
        if (input[i] == '$') {
            i++;
            // Supongamos que estamos buscando $USER
            if (strncmp(&input[i], "USER", 4) == 0) {
                printf("%s", getenv("USER"));
                i += 4;
            }
            // Puedes agregar más variables aquí...
        } else {
            putchar(input[i]);
            i++;
        }
    }
	putchar('\n');
}

int main() {

    const char *input = "Hola $USER, bienvenido a tu shell";
    const char	*input_single = "echo 'Hola $USER'";
	const char	*input_double = "echo \"Hola $USER\"";
	const char	*input_backticks = "echo `date`";
	expand_variable(input);
    handle_single_quotes(input_single);
	putchar('\n');
	handle_double_quotes(input_double);
	putchar('\n');
	handle_backticks(input_backticks);
	putchar('\n');
    return 0;
}
