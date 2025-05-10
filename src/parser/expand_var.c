/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:47:45 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/10 13:39:12 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var_value(char *value, t_shell *shell)
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
		{
			expanded = append_doll_and_char(expanded, value[i]);
			i++;
		}
	}
	return (expanded);
}

// Tal vez no es muy apropiado, revisar
static char	*strip_quotes(char *expanded)
{
	char	*tmp_expanded;

	if (expanded[0] == '\"' && expanded[ft_strlen(expanded) - 1] == '\"')
	{
		tmp_expanded = ft_substr(expanded, 1, ft_strlen(expanded) - 2);
		free(expanded);
		return (tmp_expanded);
	}
	return (expanded);
}

void	expand_variable(t_shell *shell)
{
	t_tkn	*current_token;
	char	*expanded;

	current_token = shell->tkns;
	while (current_token)
	{
		if (current_token->quote != Q_SINGLE)
		{
			expanded = expand_var_value(current_token->value, shell);
			expanded = strip_quotes(expanded);
			free(current_token->value);
			current_token->value = expanded;
		}
		current_token = current_token->next;
	}
}
