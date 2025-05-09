/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:50:58 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/29 20:00:45 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putstr(char *str, int *flag);
int		ft_tohexa(unsigned long nb, char type, int *flag);
int		ft_putunbr(unsigned int nb, int *flag);
int		ft_putnbr(long nb, int *flag);
int		ft_print_ptr(unsigned long ptr, int *flag);
void	ft_printchar(char c, int *flag);

int	ft_putchar1(char c, int *flag)
{
	write((*flag), &c, 1);
	return (1);
}

int	nq_conversion(char a, va_list args, int *flag)
{
	int	print_length;

	print_length = 0;
	if (a == 'c')
		print_length += ft_putchar1(va_arg(args, int), flag);
	else if (a == 's')
		print_length += ft_putstr(va_arg(args, char *), flag);
	else if (a == 'd' || a == 'i')
		print_length += ft_putnbr(va_arg(args, int), flag);
	else if (a == 'u')
		print_length += ft_putunbr(va_arg(args, unsigned int), flag);
	else if (a == 'p')
		print_length += ft_print_ptr(va_arg(args, unsigned long), flag);
	else if (a == 'x')
		print_length += ft_tohexa(va_arg(args, unsigned int), 'x', flag);
	else if (a == 'X')
		print_length += ft_tohexa(va_arg(args, unsigned int), 'X', flag);
	else if (a == '%')
		print_length += ft_putchar1('%', flag);
	else if (a == '2')
		*flag = 2;
	else
		return (0);
	return (print_length);
}

int	ft_printf(const char *num, ...)
{
	int		i;
	int		size;
	int		flag;
	va_list	args;

	i = 0;
	size = 0;
	flag = 1;
	va_start(args, num);
	while (num[i])
	{
		if (num[i] == '%')
		{
			i++;
			size += nq_conversion(num[i], args, &flag);
		}
		else
		{
			size += write(flag, &num[i], 1);
		}
		i++;
	}
	va_end(args);
	return (size);
}
/*int main() {
    int ap = 5466;
    int min_int = INT_MIN;
    int max_int = INT_MAX;
    unsigned int u_ap = 5466;
    unsigned long ptr = (unsigned long)&ap;
    
    printf("Custom printf: %d\n", ft_printf("Hex (lowercase): %x\n", ap));
    printf("Original printf: %d\n\n", printf("Hex (lowercase): %x\n", ap));
    
    printf("Custom printf: %d\n", ft_printf("Hex (uppercase): %X\n", ap));
    printf("Original printf: %d\n\n", printf("Hex (uppercase): %X\n", ap));
    
    printf("Custom printf: %d\n", ft_printf("Pointer address: %p\n", &ap));
    printf("Original printf: %d\n\n", printf("Pointer address: %p\n", &ap));
    
    printf("Custom printf: %d\n", ft_printf("Character: %c\n", 'A'));
    printf("Original printf: %d\n\n", printf("Character: %c\n", 'A'));
    
    printf("Custom printf: %d\n", ft_printf("String: %s\n", "Hello, World!"));
    printf("Original printf: %d\n\n", printf("String: %s\n", "Hello, World!"));
    
    printf("Custom printf: %d\n", ft_printf("Integer (decimal): %d\n", 1234));
    printf("Original printf: %d\n\n", printf("Integer (decimal): %d\n", 1234));
    
    printf("Custom printf: %d\n", 
    ft_printf("Integer (decimal, negative): %d\n", -1234));
    printf("Original printf: %d\n\n",
     printf("Integer (decimal, negative): %d\n", -1234));
    
    printf("Custom printf: %d\n", ft_printf("Unsigned integer: %u\n", u_ap));
    printf("Original printf: %d\n\n", printf("Unsigned integer: %u\n", u_ap));
    
    printf("Custom printf: %d\n", ft_printf("INT_MIN: %d\n", min_int));
    printf("Original printf: %d\n\n", printf("INT_MIN: %d\n", min_int));
    
    printf("Custom printf: %d\n", ft_printf("INT_MAX: %d\n", max_int));
    printf("Original printf: %d\n\n", printf("INT_MAX: %d\n", max_int));
    
    printf("Custom printf: %d\n", ft_printf("Percentage sign: %%\n"));
    printf("Original printf: %d\n\n", printf("Percentage sign: %%\n"));

    return 0;
}*/
