/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:06:32 by vnieto-j          #+#    #+#             */
/*   Updated: 2024/11/26 18:15:36 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	format(const char *str, int i, va_list arg, int *len)
{
	if (str[i] == 's')
		ft_print_str(va_arg(arg, char *), len);
	else if (str[i] == 'c')
		ft_print_char(va_arg(arg, int), len);
	else if (str[i] == 'p')
		ft_put_ptr((void *)va_arg(arg, void *), len);
	else if (str[i] == 'd' || str[i] == 'i')
		ft_print_nbr(va_arg(arg, int), len);
	else if (str[i] == 'u')
		ft_print_unsigned_nbr(va_arg(arg, unsigned int), len);
	else if (str[i] == 'X')
		ft_print_hex(va_arg(arg, unsigned int), 'X', len);
	else if (str[i] == 'x')
		ft_print_hex(va_arg(arg, unsigned int), 'x', len);
	else if (str[i] == '%')
		ft_print_char('%', len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	arg;

	len = 0;
	i = 0;
	if (!str)
		return (-1);
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				return (va_end(arg), -1);
			format(str, ++i, arg, &len);
		}
		else
			len += write(1, &str[i], 1);
		i++;
	}
	va_end(arg);
	return (len);
}

// int main(void)
// {
//     int num = 42;
// 	unsigned int nb = 43;
//     char *text = "Salut";
// 	char *strnull = NULL;

// 	//Test pointeur
// 	printf("\t\t\tTest pointeur\n\n");
// 	printf("%d\n", ft_printf("%p\n", NULL));
// 	printf("%d\n", printf("%p\n", NULL));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%p\n", text));
// 	printf("%d\n", printf("%p\n", text));
// 	printf("\n\n");
// 	//Test str
// 	printf("\t\t\tTest string\n\n");
// 	printf("%d\n", ft_printf("%s\n", strnull));
// 	printf("%d\n", printf("%s\n", strnull));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%s\n", text));
// 	printf("%d\n", printf("%s\n", text));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%s\n", "Bonjour \t\t tres bien merci"));
// 	printf("%d\n", printf("%s\n", "Bonjour\t\t tres bien merci"));
// 	printf("\n\n");
// 	// //Test int
// 	printf("\t\t\tTest int\n\n");
// 	printf("%d\n", ft_printf("%d\n", num));
// 	printf("%d\n", printf("%d\n", num));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%d\n", 0));
// 	printf("%d\n", printf("%d\n", 0));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%d\n", -0));
// 	printf("%d\n", printf("%d\n", -0));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%d\n", INT_MAX));
// 	printf("%d\n", printf("%d\n", INT_MAX));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%d\n", INT_MAX));
// 	printf("%d\n", printf("%d\n", INT_MAX));
// 	// //Test unsigned int
// 	printf("\t\t\tTest unsigned int\n\n");
// 	printf("%d\n", ft_printf("%u\n", nb));
// 	printf("%d\n", printf("%u\n", nb));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%u\n", 0));
// 	printf("%d\n", printf("%u\n", 0));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%u\n", -0));
// 	printf("%d\n", printf("%u\n", -0));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%u\n", -42));
// 	printf("%d\n", printf("%u\n", -42));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%u\n", INT_MAX));
// 	printf("%d\n", printf("%u\n", INT_MAX));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%u\n", INT_MAX));
// 	printf("%d\n", printf("%u\n", INT_MAX));
// 	// //Test Hexa
// 	printf("\t\t\tTest hexadecimal minuscule\n\n");
// 	printf("%d\n", ft_printf("%x\n", nb));
// 	printf("%d\n", printf("%x\n", nb));
// 	printf("\n");
// 	printf("%d\n", ft_printf("%x\n", -42));
// 	printf("%d\n", printf("%x\n", -42));
// 	printf("\n");
// 	printf("\t\t\tTest hexadecimal majuscule\n\n");
// 	printf("%d\n", ft_printf("%X\n", nb));
// 	printf("%d\n", printf("%X\n", nb));
// 	printf("\n");
// 	// test
// 	printf("\t\t\tTest pourcentage\n\n");
// 	printf("%d\n", printf("%%\n"));
// 	printf("%d\n", ft_printf("%%\n"));
// 	// ft_printf("%s\n", n);
// 	// printf("%s\n", n);
// 	// ft_printf("%c\n\n\n", c);
// 	// printf("%d", ft_printf("%%%hola\n"));
// }