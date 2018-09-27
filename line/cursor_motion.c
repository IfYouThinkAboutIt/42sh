/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmdaba <rmdaba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 06:53:04 by rmdaba            #+#    #+#             */
/*   Updated: 2018/09/03 15:40:23 by rmdaba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	set_curpos(t_line *line)
{
	size_t	xpos;
	size_t	ypos;

	xpos = line->start.col + line->cur % line->winsz.col;
	ypos = line->start.row + line->cur / line->winsz.col;
	if (xpos > line->winsz.col)
	{
		xpos %= line->winsz.col;
		ypos++;
	}
	tputs(tgoto(tgetstr("cm", NULL), xpos - 1, ypos - 1), 0, &ft_putchar);
}

void	cur_to_end(t_line *line)
{
	line->cur = line->length;
	set_curpos(line);
}

void	cur_to_home(t_line *line)
{
	line->cur = 0;
	set_curpos(line);
}

void	cur_to_left(t_line *line)
{
	if (!line->cur)
		return ;
	line->cur--;
	set_curpos(line);
}

void	cur_to_right(t_line *line)
{
	if (line->cur == line->length)
		return ;
	line->cur++;
	set_curpos(line);
}
