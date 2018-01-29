/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-souz <fde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:50:24 by fde-souz          #+#    #+#             */
/*   Updated: 2017/12/15 17:32:40 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		word;
	int		tab1[2];

	if (s)
	{
		tab1[0] = 0;
		tab1[1] = 0;
		word = ft_countwords(s, c);
		if (!(tab = (char **)malloc(sizeof(char *) * word + 1)))
			return (NULL);
		while (s[tab1[0]] && tab1[1] < word)
		{
			tab1[0] = ft_detectword(s, tab1[0], c);
			if (!(tab1[0] = ft_fill(s, tab, tab1, c)))
				return (NULL);
			tab1[1] += 1;
		}
		tab[tab1[1]] = NULL;
		return (tab);
	}
	return (NULL);
}
