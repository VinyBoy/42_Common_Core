/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:23 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 19:10:00 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			g_signal_status;

static void	change_shlvl(t_env *env)
{
	t_env	*tmp;
	int		shlvl;
	char	*str_shlvl;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_var, "SHLVL=", 6))
		{
			shlvl = ft_atoi(ft_get_env_var(env, "SHLVL"));
			str_shlvl = ft_itoa_mem(shlvl);
			mem_manager(FREE, 0, tmp->env_var);
			tmp->env_var = ft_strjoin_mem("SHLVL=", str_shlvl);
			mem_manager(FREE, 0, str_shlvl);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	init_data(t_data *data, char **envp)
{
	data->env = get_env(envp);
	change_shlvl(data->env);
	data->status = 0;
	data->count = 0;
	data->i = -1;
	data->here = NULL;
}

static void	handle_signal_status(t_data *data)
{
	if (g_signal_status)
	{
		data->status = g_signal_status;
		g_signal_status = 0;
	}
}

int	shell_loop(t_data *data, int *exit_status, t_cmd *cmd)
{
	while (1)
	{
		init_signals();
		data->input = readline(GREEN "minishell$" RESET " ");
		data->count++;
		handle_ctrl_d(data, exit_status);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		handle_signal_status(data);
		if (!data->input)
			continue ;
		if (data->input[0])
		{
			add_history(data->input);
			cmd = new_parsing(data);
			if (!cmd)
				continue ;
			data->status = ft_exec(data, cmd);
			(*exit_status) = data->status;
		}
		if (data->input)
			free(data->input);
	}
	free_data(data);
}

int	main(int argc, char **argv, char **envp)
{
	static t_data	*data = NULL;
	static t_cmd	*cmd = NULL;
	int				exit_status;

	(void)argc;
	(void)argv;
	if (isatty(STDIN_FILENO) == 0 || isatty(STDOUT_FILENO) == 0)
		return (ft_dprintf(2, "minishell: no tty\n"), 1);
	exit_status = 0;
	data = mem_manager(MALLOC, sizeof(t_data), NULL);
	init_data(data, envp);
	print_minishell();
	init_signals();
	shell_loop(data, &exit_status, cmd);
	return (mem_manager(FREEALL, 0, NULL), exit_status);
}
