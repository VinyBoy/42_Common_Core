/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:56:35 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/28 21:25:18 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	setup_heredoc_child(char **delim, int pipefd[2])
{
	int	in_quote;

	signal(SIGINT, sig_int_here_doc);
	close(pipefd[0]);
	in_quote = is_quoted_delim(*delim);
	*delim = clean_quotes(*delim);
	return (in_quote);
}

static int	check_heredoc_exit(char *line, char *delim, t_data *data)
{
	if (g_signal_status == 130)
	{
		close_here_doc(data);
		mem_manager(FREEALL, 0, NULL);
		exit(130);
	}
	if (!line || !ft_strcmp(line, delim))
	{
		ctrl_d_here_doc(line, delim, data);
		if (line)
			free(line);
		return (1);
	}
	return (0);
}

static void	process_hd_line(char *line, int pipefd, int in_quote, t_data *data)
{
	if (in_quote == 0)
		line = do_expand_here(line, data);
	write(pipefd, line, ft_strlen(line));
	write(pipefd, "\n", 1);
	free(line);
}

static void	cleanup_heredoc_child(int pipefd, t_data *data)
{
	close(pipefd);
	close_here_doc(data);
	mem_manager(FREEALL, 0, NULL);
	exit(0);
}

void	handle_here_doc_child(char *delim, int pipefd[2], t_data *data)
{
	char	*line;
	int		in_quote;

	in_quote = setup_heredoc_child(&delim, pipefd);
	while (1)
	{
		line = readline("> ");
		if (check_heredoc_exit(line, delim, data))
			break ;
		process_hd_line(line, pipefd[1], in_quote, data);
	}
	cleanup_heredoc_child(pipefd[1], data);
}
