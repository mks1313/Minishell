/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_to_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:10:04 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/29 17:11:07 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokens_to_args(t_tkn *tokens)
{
	int		count;
	t_tkn	*curr;
	char	**args;
	int		i;

	count = 0;
	curr = tokens;
	while (curr && curr->type != TOKEN_OPERATOR)
	{
		count++;
		curr = curr->next;
	}
	args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	curr = tokens;
	while (i < count)
	{
		args[i] = ft_strdup(curr->value);
		curr = curr->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
