/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktobo <mtoktobo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:45:32 by iklimov           #+#    #+#             */
/*   Updated: 2019/12/12 16:35:58 by mtoktobo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
    int			fd;
	int			n;
	t_tetris	*tab;

	while (argc-- > 1)
	{	
		if ((fd = open(argv[argc], O_RDONLY)) == -1)
			error(2);
		n = 0;
		tab = reader(fd, &n);
		if (n > 26)
			error(1);
		close(fd);
		int i = 0;
		
		ft_solve(tab, ft_isqrtc(n * 4));
	}
	return (0);
}
