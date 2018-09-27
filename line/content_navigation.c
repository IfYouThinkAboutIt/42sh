/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_navigation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmdaba <rmdaba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 06:52:26 by rmdaba            #+#    #+#             */
/*   Updated: 2018/08/19 06:55:11 by rmdaba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	next_word(t_line *line)
{
	while (line->cmd[line->cur] != ' ' && line->cur != line->length)
		cur_to_right(line);
	while (line->cmd[line->cur] == ' ' && line->cur != line->length)
		cur_to_right(line);
}

void	prev_word(t_line *line)
{
	if (line->cur && line->cmd[line->cur - 1] == ' ')
		cur_to_left(line);
	while (line->cmd[line->cur] == ' ' && line->cur)
		cur_to_left(line);
	while (line->cmd[line->cur] != ' ' && line->cur)
		cur_to_left(line);
	if (line->cur)
		cur_to_right(line);
}

void	next_line(t_line *line)
{
	line->cur = line->cur + line->winsz.col > line->length ?
		line->length : line->cur + line->winsz.col;
	set_curpos(line);
}

void	prev_line(t_line *line)
{
	line->cur = line->cur < line->winsz.col ? 0 : line->cur -
		line->winsz.col;
	set_curpos(line);
}
