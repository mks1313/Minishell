/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:02:38 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/03 21:34:01 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../libft/includes/libft.h"

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

void handle_double_quotes(const char *inpt, char **envp)
{
	int		i;
	int		j;
	char	var_name[256];
	char	*var_val;

	i = 0;
	while (inpt[i])
	{
		if (inpt[i] == '"')
		{
			i++; // Saltar la comilla de apertura
			while (inpt[i] && inpt[i] != '"')
			{
				if (inpt[i] == '$')
				{
					i++;
					j = 0;
					// Recoger el nombre de al variable del entorno
					while (inpt[i] && (ft_isalnum(inpt[i]) || inpt[i] == '_'))
						var_name[j++] = inpt[i++];
					// Termianr la cadena del nombre de la var del entorno
					var_name[j] = '\0';
					// Obtener el valor de la variable del entornno
					var_val = ft_getenv(var_name, envp);
					if (var_val)
						ft_printf("%s", var_val);
				}
				else
				{
					ft_putchar(inpt[i]);
					i++;
				}
			}
			i++; // Saltar la comilla de cierre
		} 
		else
		{
			ft_putchar(inpt[i]);
			i++;
		}
	}
}

void	expand_variable(const char *inpt, char **envp)
{
	int	i;

	i = 0;
	while (inpt[i])
	{
		if (inpt[i] == '$')
		{
			i++;
			int var_start = i;
			// Buscar el fin del nombre de la variable (alfanumérica o guion bajo)
			while (ft_isalnum(inpt[i]) || inpt[i] == '_') {
				i++;
			}
			// Extraer el nombre de la variable
			char var_name[256];  // Asegúrate de que el tamaño sea suficiente
			ft_strncpy(var_name, &inpt[var_start], i - var_start);
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
			ft_putchar(inpt[i]);
			i++;
		}
	}
	ft_putchar('\n');
}
/*
int main(int ac, char **av, char **envp)
{
	char *string;

    (void)av;
	while (1)
	{
		string = readline("minishell> ");
		if (!string) // Manejo de Ctrl+D (EOF)
			break;
		if (ft_strcmp(string, "exit") == 0)
		{
			free(string);
			break;
		}
		expand_variable(string, envp);
		free(string);
	}
	return 0;
}*/
