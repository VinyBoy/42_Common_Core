/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:35:18 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/07/28 15:46:46 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/types.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*
	*@Libft
*/
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isprint(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t dst_size);
size_t	ft_strlcat(char *dst, const char *src, size_t dest_size);
void	ft_bzero(void *string, size_t n);
void	*ft_memcpy(void *dest, const void *source, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *pointer, int value, size_t count);
char	*ft_strchr(const char *str, int searchedchar);
char	*ft_strrchr(const char *str, int searchedchar);
char	*ft_strdup(const char *source);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size);
int		ft_atoi(const char *TheString);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*
	*@ft_printf
*/
# ifndef STD_OUT
#  define STD_OUT 1
# endif

int		ft_hex_len(unsigned	int num);
void	ft_put_hex(unsigned int num, const char format);
int		ft_print_hex(unsigned int num, const char format);
int		ft_tcheck(int n);
char	*ft_itoa_pf(int n);
int		ft_print_nbr(int n);
int		ft_print_char(char c);
int		ft_print_str(char *str);
int		ft_strlen_printf(char *str);
int		ft_putstr(char *str);
int		ptrbase(unsigned long num, char *base, int *len);
int		put_ptr(void *ptr);
int		ft_uputstr(char *str);
int		ft_unsigned_tcheck(unsigned int n);
char	*ft_unsigned_itoa(unsigned int n);
int		ft_print_unsigned_nbr(unsigned int n);
int		format(const char *str, int i, va_list arg);
int		ft_printf(const char *str, ...);
/*
	*@Get_next_line
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		ft_one(char *stash);
char	*ft_join(char *buff, char *stash);
int		ft_check_new_line(char *stash);
int		strln(char *str);
int		strlnao(char *str, char c);
void	init_and_put_one(char *stash, char c);
char	*ft_join(char *buff, char *stash);
char	*ft_join_new_line(char *buff, char *stash);
char	*get_next_line(int fd);
char	*init_buff(void);
char	*ft_condtion(char stash[BUFFER_SIZE], int fd, char *buff);

#endif
