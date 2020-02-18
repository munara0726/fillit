/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iklimov <iklimov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:14:33 by iklimov           #+#    #+#             */
/*   Updated: 2019/12/12 16:46:07 by mtoktobo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <fcntl.h>

t_tetris	*new_tetr(t_tetris **tab)
{
	int		i;
	int		j;
	t_tetris static *tail = NULL;
	t_tetris *new;

	new = malloc(sizeof(t_tetris));
	if (!*tab || !tail)
	{
		tail = new;
		*tab = new;
	}
	else
	{
		tail->next = new;
		tail = tail->next;
	}
	tail->next = NULL;
	j = -1;
	while (++j < 4)
		tail->x[0][j] = -1;
	while (--j > -1)
		tail->x[1][j] = -1;
	return (tail);
}

void	ft_move(t_tetris *tab)
{
	int minx;
	int miny;
	int i;

	minx = tab->x[0][0];
	miny = tab->x[1][0];
	i = 0;
	while (++i < 4)
	{
		if (tab->x[0][i] < minx)
			minx = tab->x[0][i];
		if (tab->x[1][i] < miny)
			miny = tab->x[1][i];
	}
	while (--i > -1)
	{
		tab->x[0][i] -= minx;
		tab->x[1][i] -= miny;
	}
}

int		tetr_add(t_tetris *tab, int n)
{
	int i;
	int j;
	int connection;

	i = 0;
	while(tab->x[0][i] != -1)
		i++;
	if (i > 3)
		return (0);
	tab->x[0][i] = n % 5;
	tab->x[1][i] = n / 5;
	if (i == 3)
	{
		connection = 0;
		i = -1;
		while (++i < 4)
		{
			j = -1;
			while (++j < 4)
				if ((((tab->x[0][i] == tab->x[0][j]) != (tab->x[1][i] == tab->x[1][j]))
							&& ((tab->x[0][i] - tab->x[0][j] == -1 || tab->x[0][i] - tab->x[0][j] == 1)
								|| (tab->x[1][i] - tab->x[1][j] == -1 || tab->x[1][i] - tab->x[1][j] == 1))))
					connection++;
		}
		if (connection != 6 && connection != 8)
			return (0);
		ft_move(tab);
	}
	return (1);
}

int		validate(char *buff, int bytesread, t_tetris *tab)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (i < bytesread && buff[i] != '\0')
	{
		if ((i % 5 < 4 && (buff[i] == '.' || buff[i] == '#'))
				|| (i == 20 && buff[i] == '\n'))
		{
			if (buff[i] == '#')
				if (++num && !tetr_add(tab, i))
					return (0);
			i++;
		}
		else if (i % 5 == 4 && (buff[i] == '\n' || buff[i] == '\0'))
			i++;
		else
			return (0);
	}
	if (i < 20 || num != 4)
		return (0);
	return (1);
}

void		list_dell(t_tetris **tab)
{
	t_tetris *temp;
	while (tab && *tab)
	{
		temp = (**tab).next;
		free(*tab);
		*tab = temp;
	}
}

t_tetris	*reader(int fd, int *n)
{
	int			bytesread = 21;
	char		buff[22];
	t_tetris	*tab;
	t_tetris	*tail;

	tab = NULL;
	while (bytesread == 21)
	{
		bytesread = read(fd, buff, 21);
		buff[bytesread] = '\0';
		tail = new_tetr(&tab);
		if ((++(*n)) && validate(buff, bytesread, tail) == 0)
		{
			error(1);
			list_dell(&tab);
			break ;
		}
	}
	return (tab);
}
