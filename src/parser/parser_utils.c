/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:53:56 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/10 13:42:04 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	return (cmd);
}

static void	init_cmd_args(t_cmd *cmd, char *arg)
{
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
		return ;
	cmd->args[0] = ft_strdup(arg);
	cmd->args[1] = NULL;
	cmd->cmd = cmd->args[0];
}

static void	append_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	while (cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	j = 0;
	while (j < i)
	{
		new_args[j] = cmd->args[j];
		j++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args)
	{
		free(new_args);
		return ;
	}
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	if (!cmd || !arg)
		return ;
	if (!cmd->args)
		init_cmd_args(cmd, arg);
	else
		append_arg_to_cmd(cmd, arg);
}

void	process_input(const char *input, t_shell *shell)
{
	t_tkn	*tokens;

	tokens = tokenize_input((char *)input);
	if (!tokens)
		return ;
	shell->tkns = tokens;
	expand_variable(shell);
}

void	add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!new_cmd)
		return ;
	if (!*cmd_list)
		*cmd_list = new_cmd;
	else
	{
		tmp = *cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}
