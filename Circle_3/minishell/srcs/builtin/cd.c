/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:10:51 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 00:10:51 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_oldpwd(t_env *env, char *path)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_var, "OLDPWD=", 7))
		{
			mem_manager(FREE, 0, tmp->env_var);
			tmp->env_var = ft_strjoin_mem("OLDPWD=", path);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	update_pwd(t_env *env, char *path)
{
	char	pwd[4096];
	t_env	*tmp;

	update_oldpwd(env, path);
	if (getcwd(path, 4096) == NULL)
	{
		ft_dprintf(2, "%s%sNo such file or directory\n", CH, CWD);
		return ;
	}
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_var, "PWD=", 4))
		{
			mem_manager(FREE, 0, tmp->env_var);
			tmp->env_var = ft_strjoin_mem("PWD=", pwd);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	ft_cd_three(t_data *data, char **strs)
{
	DIR	*dir;

	dir = opendir(strs[1]);
	if (dir == NULL && access(strs[1], F_OK) == 0)
	{
		ft_dprintf(2, "minishell: cd: %s: Not a directory\n", strs[1]);
		data->status = 1;
		return ;
	}
	if (dir)
		closedir(dir);
}

static void	ft_cd_two(t_data *data, char **strs, int cd, char path[4096])
{
	if (strs[1][0] == '-' && strs[1][1] != '\0')
	{
		ft_dprintf(2, "minishell: cd: %c%c: invalid option\n", strs[1][0],
			strs[1][1]);
		data->status = 2;
		return ;
	}
	ft_cd_three(data, strs);
	if (data->status != 0)
		return ;
	if (strs[1][0] == '~' && strs[1][1] == '\0')
		cd = chdir(ft_get_env_var(data->env, "HOME"));
	else if (strs[1][0] == '-' && strs[1][1] == '\0')
		cd = chdir(ft_get_env_var(data->env, "OLDPWD"));
	else
		cd = chdir(strs[1]);
	if (cd == 0)
		update_pwd(data->env, path);
	else
	{
		ft_dprintf(2, "minishell: cd: %s: No such file or directory\n", strs[1]);
		data->status = 1;
		return ;
	}
}

void	ft_cd(char **strs, t_data *data)
{
	char	path[4096];
	int		cd;

	cd = 0;
	if (getcwd(path, 4096) == NULL)
	{
		ft_dprintf(2, "%s%sNo such file or directory\n", CH, CWD);
		return ;
	}
	if (count_args(strs) == 1)
	{
		cd = chdir(ft_get_env_var(data->env, "HOME"));
		if (cd == 0)
			update_pwd(data->env, path);
	}
	else if (count_args(strs) == 2)
		return (ft_cd_two(data, strs, cd, path));
	else
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		data->status = 1;
		return ;
	}
	data->status = 0;
}
