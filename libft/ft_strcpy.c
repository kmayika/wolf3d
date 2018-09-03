/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmayika <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 10:07:46 by kmayika           #+#    #+#             */
/*   Updated: 2018/05/24 15:10:57 by kmayika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	x;

	x = 0;
	while (src[x] != '\0' && src[x] != 0)
	{
		dst[x] = src[x];
		x++;
	}
	dst[x] = '\0';
	return (dst);
}