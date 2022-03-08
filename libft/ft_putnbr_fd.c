/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:21 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_nbr(int i, int fd)
{
	ft_putchar_fd('0' + i, fd);
}

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	nbr;

	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nb;
	}
	else
		nbr = nb;
	if (nbr / 10 == 0)
		print_nbr(nbr, fd);
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		print_nbr(nbr % 10, fd);
	}
}
