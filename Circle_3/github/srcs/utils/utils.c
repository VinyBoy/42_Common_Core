/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:50:29 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/28 19:11:32 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Affichage du grand MINISHELL */
void	print_minishell(void)
{
	printf("\033[32;1m __       __  ______  __    __  ______   ______   __    __  ________  __        __  \n\
/  \\     /  |/      |/  \\  /  |/      | /      \\ /  |  /  |/        |/  |      /  |\n\
$$  \\   /$$ |$$$$$$/ $$  \\ $$ |$$$$$$/ /$$$$$$  |$$ |  $$ |$$$$$$$$/ $$ |      $$ |\n\
$$$  \\ /$$$ |  $$ |  $$$  \\$$ |  $$ |  $$ \\__$$/ $$ |__$$ |$$ |__    $$ |      $$ |\n\
$$$$  /$$$$ |  $$ |  $$$$  $$ |  $$ |  $$      \\ $$    $$ |$$    |   $$ |      $$ |\n\
$$ $$ $$/$$ |  $$ |  $$ $$ $$ |  $$ |   $$$$$$  |$$$$$$$$ |$$$$$/    $$ |      $$ |\n\
$$ |$$$/ $$ | _$$ |_ $$ |$$$$ | _$$ |_ /  \\__$$ |$$ |  $$ |$$ |_____ $$ |_____ $$ |_____\n\
$$ | $/  $$ |/ $$   |$$ | $$$ |/ $$   |$$    $$/ $$ |  $$ |$$       |$$       |$$       |\n\
$$/      $$/ $$$$$$/ $$/   $$/ $$$$$$/  $$$$$$/  $$/   $$/ $$$$$$$$/ $$$$$$$$/ $$$$$$$$/ \n\
\n%s", RESET);
}

/* un write basique qui ecrit sur le stderr */
void	write_error(char *str)
{
	write(2, str, ft_strlen(str));
}

/* Compte le nombre d'arguments */
int	count_args(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

/* Compte le nombre de noeuds dans un t_env* */
int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
