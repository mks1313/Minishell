/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:59:37 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 20:49:15 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Appends a character to the expanded string.
 */
char	*append_doll_and_char(char *expanded, char next_char)
{
	char	tmp[2];
	char	*aux;

	tmp[0] = next_char;
	tmp[1] = '\0';
	aux = ft_strjoin(expanded, tmp);
	free(expanded);
	return (aux);
}

/**
 * Expands the value of a variable by handling
 * dollar signs and performing variable expansion.
 */
char	*expand_var_value(char *value, t_shell *shell)
{
	int		i;
	char	*expanded;
	char	*tmp;
	char	*aux;

	i = 0;
	expanded = ft_strdup("");
	while (value[i])
	{
		if (value[i] == '$')
		{
			tmp = handle_dollar_sign(value, &i, shell);
			aux = ft_strjoin(expanded, tmp);
			free(expanded);
			free(tmp);
			expanded = aux;
		}
		else
			expanded = append_doll_and_char(expanded, value[i++]);
	}
	return (expanded);
}

/**
 * Expands all variables in the shell’s token list.
 * It iterates through each token and expands any variable references.
 */
void	expand_variable(t_shell *shell)
{
	t_tkn		*curr;
	t_tkn_part	*part;
	char		*expanded;

	curr = shell->tkns;
	while (curr)
	{
		part = curr->parts;
		while (part)
		{
			if (part->quote != Q_SINGLE)
			{
				expanded = expand_var_value(part->value, shell);
				free(part->value);
				part->value = expanded;
			}
			part = part->next;
		}
		curr = curr->next;
	}
}
