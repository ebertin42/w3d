/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loup.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:57:02 by vgauther          #+#    #+#             */
/*   Updated: 2018/02/05 15:23:59 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define _RE "\033[0m "
#define _MI "\033[32m-> \033[36m"
#define _NNL "\033[47m\033[30m%\033[0m"
#define _BLK "\033[30m"
#define _R "\033[31m"
#define _G "\033[32m"
#define _Y "\033[33m"
#define _BLU "\033[34m"
#define _M "\033[35m"
#define _C "\033[36m"
#define _W "\033[37m"
#define _SBLK "\033[40m"
#define _SR "\033[41m"
#define _SG "\033[42m"
#define _SY "\033[43m"
#define _SBLU "\033[44m"
#define _SM "\033[45m"
#define _SC "\033[46m"
#define _SW "\033[47m"

static void		fstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0')
			ft_putstr(_R);
		if (str[i] == 'Z')
			ft_putstr(_G);
		write(1, &str[i], 1);
		i++;
		ft_putstr(_RE);
	}
}

int				main(void)
{
	int		fd;
	int		ret;
	char	**tab;
	char	buf[5000];

	fd = open("Mke_src/leloup", O_RDONLY);
	ret = read(fd, buf, 5000);
	buf[ret] = 0;
	tab = ft_strsplit(buf, '\n');
	fd = 0;
	while (tab[fd])
	{
		fstr(tab[fd]);
		if (tab[fd + 1])
			write(1, "\n", 1);
		fd++;
	}
	ft_putstr(_RE);
	return (0);
}
