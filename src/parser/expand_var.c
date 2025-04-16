/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:02:38 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/16 10:34:23 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result = ft_strjoin(s1, s2);
	free(s1);
	return result;
}

static char	*ft_strjoin_char(char *s, char c)
{
	char	*str;
	int		len = ft_strlen(s);

	str = malloc(len + 2);
	if (!str)
		return NULL;
	ft_strcpy(str, s);
	str[len] = c;
	str[len + 1] = '\0';
	free(s);
	return str;
}

void expand_variable(t_shell *shell)
{
	t_tkn	*current_token = shell->tkns;
	int		i, start;
	char	*expanded;
	char	*tmp;
	char	*val;

	while (current_token)
	{
		if (!current_token->single_quote)
		{
			i = 0;
			expanded = ft_strdup("");
			while (current_token->value[i])
			{
				if (current_token->value[i] == '$')
				{
					i++;
					if (current_token->value[i] == '?')
					{
						tmp = ft_itoa(shell->exit_status);
						expanded = ft_strjoin_free(expanded, tmp);
						free(tmp);
						i++;
					}
					else if (ft_isalnum(current_token->value[i]) || current_token->value[i] == '_')
					{
						start = i;
						while (ft_isalnum(current_token->value[i]) || current_token->value[i] == '_')
							i++;
						tmp = ft_substr(current_token->value, start, i - start);
						val = ft_getenv(tmp, shell->env);
						if (val)
							expanded = ft_strjoin_free(expanded, val);
						free(tmp);
					}
					else
					{
						expanded = ft_strjoin_char(expanded, '$');
						expanded = ft_strjoin_char(expanded, current_token->value[i++]);
					}
				}
				else
				{
					expanded = ft_strjoin_char(expanded, current_token->value[i++]);
				}
			}

			if (expanded[0] == '\"' && expanded[ft_strlen(expanded) - 1] == '\"')
			{
				char *tmp_expanded = ft_substr(expanded, 1, ft_strlen(expanded) - 2);
				free(expanded);
				expanded = tmp_expanded;
			}
			if (expanded[0] == '\'' && expanded[ft_strlen(expanded) - 1] == '\'')
			{
				char *tmp_expanded = ft_substr(expanded, 1, ft_strlen(expanded) - 2);
				free(expanded);
				expanded = tmp_expanded;
			}

			free(current_token->value);
			current_token->value = expanded;
		}
		current_token = current_token->next;
	}
}
