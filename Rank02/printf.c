/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:27:05 by aanghel           #+#    #+#             */
/*   Updated: 2022/02/16 05:39:22 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int ft_pustr(char *str)
{
    int i;
    if (!str)
        str = "(null)";
    while (str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
    return (i);
}

int ft_putint(int i)
{
    int count = 0;

    if ( i < 0)
    {
        count += ft_putchar('-');
        i *= -1;
    }
    count += ft_putnbr(i, 10);
    return (i); 
}

int ft_putnbr(unsigned int i, int base)
{
    char *besa = "0123456789abcdef";
    int n = i % base;
    int count = 0;
    
    if (i / base > 0)
        count += ft_putnbr(i / base, base);
    count += ft_putchar(besa[n]);
    return (count);
}

int printf (char *string, ...)
{
    int i;
    va_list var;
    int count ;
    
    i = 0;
    count = 0;
    va_start(var, string);
    while (string[i])
    {
        if (string[i] == '%')
        {
            i++;
            if (string[i] == 's')
                count += ft_putstr(va_arg(var, char *));
            if (string[i] == 'd')
                count += ft_putint(va_arg(var,int));
            if (string[i] == 'x')
                count += ft_putnbr(va_arg(var, unsigned int), 16);
        }
        else
            count += ft_putchar(string[i]);
        i++;
    }
    va_end(var);
    return (count);
}