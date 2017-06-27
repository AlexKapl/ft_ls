/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 19:19:07 by akaplyar          #+#    #+#             */
/*   Updated: 2017/04/17 19:19:08 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_dir_path(char *dir, char *name)
{
	char		*tmp;
	char		*tmp1;

	tmp = ft_strjoin(dir, "/");
	tmp1 = ft_strjoin(tmp, name);
	free(tmp);
	return (tmp1);
}
