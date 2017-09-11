#include "ft_ls.h"

char			*ls_dir_path(char *dir, char *name)
{
	char		*tmp;
	char		*tmp1;

	if (ft_strequ(dir, "."))
		return (ft_strdup(name));
	else
	{
		tmp = ft_strjoin(dir, "/");
		tmp1 = ft_strjoin(tmp, name);
		free(tmp);
		return (tmp1);
	}
}

void			ls_del_dirs(void *data, size_t size)
{
	char		*name;

	(void)size;
	name = (char*)data;
	if (name)
		free(name);
}