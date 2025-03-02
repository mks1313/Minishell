/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:02:38 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/01 12:16:17 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../libft/includes/libft.h"

//extern char	**environ;

void	handle_single_quotes(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++; // Saltar la comilla de apertura
			while (input[i] && input[i] != '\'')
			{
				ft_putchar(input[i]);
				i++;
			}
			i++; // Saltar la comilla de cierre
		} else
		{
			ft_putchar(input[i]);
			i++;
		}
	}
}

void handle_double_quotes(const char *input, char **envp)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			i++; // Saltar la comilla de apertura
			while (input[i] && input[i] != '"')
			{
				if (input[i] == '$')
				{
					i++;
					// Aquí buscaríamos la variable de entorno, por ejemplo, $USER
					if (ft_strncmp(&input[i], "USER", 4) == 0)
					{
						ft_printf("%s", ft_getenv("USER", envp));
						i += 4;
					}
				} 
				else
				{
					ft_putchar(input[i]);
					i++;
				}
			}
			i++; // Saltar la comilla de cierre
		} 
		else
		{
			ft_putchar(input[i]);
			i++;
		}
	}
}

void	expand_variable(const char *input, char **envp)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			int var_start = i;
			// Buscar el fin del nombre de la variable (alfanumérica o guion bajo)
			while (ft_isalnum(input[i]) || input[i] == '_') {
				i++;
			}
			// Extraer el nombre de la variable
			char var_name[256];  // Asegúrate de que el tamaño sea suficiente
			ft_strncpy(var_name, &input[var_start], i - var_start);
			var_name[i - var_start] = '\0';
			// Obtener el valor de la variable de entorno
			char *value = ft_getenv(var_name, envp);
			if (value)
				ft_printf("%s", value);  // Imprimir el valor de la variable
			/*else {
			// Si no existe la variable, imprimimos el nombre literal
			//ft_printf("$%s", var_name);
			}*/
		}
		else
		{
			ft_putchar(input[i]);
			i++;
		}
	}
	ft_putchar('\n');
}


# define RESET	"\033[0m"
# define RED	"\033[38;5;203m"
# define GOLD	"\033[38;5;220m"
# define GREEN	"\033[38;5;120m"
/*
int main(int ac, char **av, char **envp)
{
	char *string;

    (void)av;
	string = (char *)malloc(sizeof(char) * 100);
	if (!string)
		return (ft_printf("ERROR MALLOC"));
	while (1)
	{
		scanf("%s", string);
		expand_variable(string, envp);
	}
	//casos para variables eistetes
	const char	*input = "Hola $USER, bienvenido a tu shell";
	const char	*input_path = "Hola $USER, tu path es: $PATH";
	// Casos para vars que NO existen
	const char	*input_no_exist_var = "Hola $NO_EXISTE, esta var no existe";
	const char	*input_no_exist_path = "Intentando acceder a $NO_PATH";
	//Casos con comillas dobles simples y backticks
	const char	*input_single = "echo 'Hola $USER'";
	const char	*input_double = "echo \"Hola $USER\"";
	ft_printf(RED "\n=== Casos con variables existentes ===\n\n" RESET);
	expand_variable(input, envp);
	expand_variable(input_path, envp);

	ft_printf(RED "\n=== Casos con var que no existen ===\n\n" RESET);
	expand_variable(input_no_exist_var, envp);
	expand_variable(input_no_exist_path, envp);

	ft_printf(RED"\n=== Casos con commillas ===\n\n"RESET);
	handle_single_quotes(input_single);
	ft_putchar('\n');
	handle_double_quotes(input_double, envp);
	ft_putchar('\n');

	return 0;
}*/
