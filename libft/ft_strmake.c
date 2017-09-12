/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 14:45:12 by akaplyar          #+#    #+#             */
/*   Updated: 2017/09/12 14:45:13 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmake(char **s1, char **s2, int del)
{
	char	*str;

	str = ft_strjoin(*s1, *s2);
	if (del == 1 || del == 3)
		if (*s1)
		{
			free(*s1);
			*s1 = NULL;
		}
	if (del == 2 || del == 3)
		if (*s2)
		{
			free(*s2);
			*s2 = NULL;
		}
	return (str);
}
