/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 21:15:19 by akaplyar          #+#    #+#             */
/*   Updated: 2017/09/12 21:16:04 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ls_errors(int errnum, char *invalid)
{
	if (errnum == OPT_ERR)
		ft_printf("{fd}ft_ls: illegal option -- %.1s\n%s{eofd}", 2, invalid,
							"usage: ft_ls [-ARSacfiklnprstu1@] [file ...]\n");
	else if (errnum == MLC_ERR)
		ft_printf("{fd}Error: can't allocate memory\n{eofd}", 2);
	exit(errnum);
}

char			*ls_dir_path(char *dir, char *name)
{
	char		*tmp;

	if (ft_strequ(dir, "."))
		return (ft_strdup(name));
	else
	{
		if (!ft_strequ(dir, "/"))
		{
			tmp = ft_strjoin(dir, "/");
			tmp = ft_strmake(&tmp, &name, 1);
			return (tmp);
		}
		else
			return (ft_strjoin(dir, name));
	}
}

void			ls_list(t_info **info, t_ls *ls)
{
	t_list		*node;

	if (!(node = (t_list*)malloc(sizeof(t_list))))
		ls_errors(MLC_ERR, NULL);
	if (!ls->l || (*info)->err)
	{
		(*info)->time = NULL;
		(*info)->perm = NULL;
		(*info)->user = NULL;
		(*info)->group = NULL;
	}
	node->content = (void*)*info;
	node->content_size = 0;
	node->next = NULL;
	ft_lst_push_back(&ls->list, node);
}

t_list			*ls_new_dir(t_info *info)
{
	t_list		*node;

	if (!(node = (t_list*)malloc(sizeof(t_list))))
		ls_errors(MLC_ERR, NULL);
	if (!(node->content = (void*)ft_strdup(info->path)))
		ls_errors(MLC_ERR, NULL);
	node->content_size = 1;
	node->next = NULL;
	return (node);
}

void			ls_del(void *data, size_t size)
{
	t_info		*info;
	char		*dir;

	if (size)
	{
		if ((dir = (char*)data))
			free(dir);
	}
	else
	{
		info = (t_info *)data;
		free(info->path);
		free(info->name);
		if (info->time)
			free(info->time);
		if (info->perm)
			free(info->perm);
		if (info->user)
			free(info->user);
		if (info->group)
			free(info->group);
		free(info);
	}
}
