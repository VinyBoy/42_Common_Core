/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:40:03 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/30 16:45:11 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*init_buffer(void)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	return (buffer);
}

char	*ft_join_new_line_detected(char *buff, char *stash)
{
	int		i;
	int		j;
	char	*new_buff;

	i = -1;
	j = 0;
	new_buff = malloc(sizeof(char) * (strln(buff) + strlnao(stash, '\n') + 2));
	if (!new_buff)
		return (NULL);
	while (buff[++i])
		new_buff[i] = buff[i];
	while (stash[j] == -1)
		j++;
	while (stash[j] != '\n')
	{
		new_buff[i] = stash[j];
		i++;
		j++;
	}
	new_buff[i] = '\n';
	i++;
	new_buff[i] = '\0';
	ft_init_and_put_one(stash, '\n');
	free (buff);
	return (new_buff);
}

char	*ft_join(char *buff, char *stash)
{
	int		i;
	int		j;
	char	*new_buff;

	i = -1;
	j = 0;
	new_buff = malloc(sizeof(char) * (strln(buff) + strlnao(stash, '\0') + 1));
	if (!new_buff)
		return (NULL);
	while (buff[++i])
		new_buff[i] = buff[i];
	while (stash[j] == -1)
		j++;
	while (stash[j] && stash[j] != -1)
	{
		new_buff[i] = stash[j];
		i++;
		j++;
	}
	new_buff[i] = '\0';
	ft_init_and_put_one(stash, '\0');
	free(buff);
	return (new_buff);
}

char	*ft_condition(char stash[BUFFER_SIZE], int fd, char *buffer, int n)
{
	while (1)
	{
		if (ft_one(stash) == 0)
		{
			n = read(fd, stash, BUFFER_SIZE);
			if (n == 0)
				break ;
			if (n == -1)
				return (free(buffer), NULL);
		}
		if (ft_check_new_line(stash) == 0)
		{
			buffer = ft_join(buffer, stash);
			if (!buffer)
				return (NULL);
		}
		if (ft_check_new_line(stash) == 1)
		{
			buffer = ft_join_new_line_detected(buffer, stash);
			if (!buffer)
				return (NULL);
			break ;
		}
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	stash[BUFFER_SIZE];
	int			n;

	n = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = init_buffer();
	if (!buffer)
		return (NULL);
	buffer = ft_condition(stash, fd, buffer, n);
	if (!buffer)
		return (NULL);
	if (buffer[0] == '\0')
		return (free(buffer), NULL);
	return (buffer);
}
// int    main(void)
// {
//     int    fd;
//     char    *t;
//     int    i;

//  	i = 1;
//     fd = open("fd", O_RDONLY);
//     t = malloc(sizeof(char) * 1);
//     t[0] = '\0';
//     while (t != NULL)
//     {
//       	free(t);
//         printf("APPEL %d : \t\n", i);
//         t = get_next_line(fd);
//         printf("%s\t", t);
//         i++;
//     }
// 	free(t);
// }
