/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:25:47 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/09 11:56:57 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TYPES_H
# define SHELL_TYPES_H

/*Manage enviroment variables*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*Commands & redirections*/
typedef struct s_cmd
{
	char			*command; //Command to execute
	char			**args; //Command args
	char			*input_file; // Input file(for redirections)
	char			*output_file; // Output file(for redirections)
	int				append_output;
	bool			pipe;//Check if the command is pipe
	int				error_redirect; //To redirect flow of errors
	bool			heredoc; // To handke input inheritance
	struct s_cmd	*next; // To manage multiplice commands
}	t_cmd;

/*Shell data*/
typedef struct s_data
{
	t_env			*env;//Enviroment variables
	t_cmd			*cmd_list;// List of commands(if ejxecute multimples cnds)
	char			*cur_dir;
	int				status;//State of exit of the last command
}	t_data;

#endif
