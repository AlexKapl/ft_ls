#include "ft_ls.h"

void		ls_list(t_info *info, t_ls *ls)
{
	t_list	*node;

	if (!(node = (t_list*)malloc(sizeof(t_list))))
		exit(123);
	node->content = (void*)info;
	node->content_size = sizeof(t_info) + ft_strlen(info->path) + ft_strlen(info->name);
	node->next = NULL;
	ft_lst_push_back(&ls->list, node);
}

t_list		*ls_new_dir(t_info *info)
{
	char	*path;
	t_list	*node;

	path = ft_dir_path(info->path, info->name);
	node = (t_list*)malloc(sizeof(t_list));
	node->content = (void*)path;
	node->content_size = ft_strlen(path);
	node->next = NULL;
	return (node);
}

static void	ls_del(void *data, size_t size)
{
	t_info	*info;

	info = (t_info*)data;
	(void)size;
	if (info)
	{
		free(info->path);
		free(info->name);
		free(info);
	}
}

void		ls_clear(t_ls *ls, t_list *dirs)
{
	ls->width[0] = 0;
	ls->width[1] = 0;
	ls->width[2] = 0;
	ls->width[3] = 0;
	if (ls->list)
		ft_lstdel(&ls->list, ls_del);
	ls->list = NULL;
	if (dirs && (ls->flags[3] || ls->flags[5]))
	{
		ls->flags[5] = 0;
		ls_readdir(dirs, ls);
	}
}

void		ls_check_width(t_ls *ls, t_info *info)
{
	char	*str;
	int		i;
	t_pass	*pass;

	if (ls->flags[0])
	{
		str = ft_llitoa(info->links);
		i = (int)ft_strlen(str);
		ls->width[0] = (ls->width[0] < i ? i : ls->width[0]);
		free(str);
		pass = getpwuid(info->user);
		i = (int)ft_strlen(pass->pw_name);
		ls->width[1] = (ls->width[1] < i ? i : ls->width[1]);
		i = (int)ft_strlen(getgrgid(info->group)->gr_name);
		ls->width[2] = (ls->width[2] < i ? i : ls->width[2]);
		str = ft_llitoa(info->size);
		i = (int)ft_strlen(str);
		ls->width[3] = (ls->width[3] < i ? i : ls->width[3]);
		free(str);
	}
}