/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:56:01 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 16:11:32 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_redirs(t_redirs *r)
{
	if (!r)
	{
		printf("  redirs: (none)\n");
		return ;
	}
	printf("  redirs:\n");
	while (r)
	{
		printf("    %s %s\n", redir_type_name(r->type), r->file);
		r = r->next;
	}
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !args[0])
	{
		printf("  args: (none)\n");
		return ;
	}
	printf("  args:");
	while (args[i])
	{
		printf(" [%d]='%s'", i, args[i]);
		i++;
	}
	printf("\n");
}

// void	print_cmds(t_cmd *cmd)
// {
// 	int	idx;

// 	idx = 0;
// 	while (cmd)
// 	{
// 		printf("Command #%d:\n", idx++);
// 		print_args(cmd->args);
// 		print_redirs(cmd->redirs);
// 		printf("  is_pipe: %s\n\n", cmd->is_pipe ? "yes" : "no");
// 		cmd = cmd->next;
// 	}
// }
