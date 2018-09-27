/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmdaba <rmdaba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 06:52:22 by rmdaba            #+#    #+#             */
/*   Updated: 2018/08/24 14:37:07 by rmdaba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include <curses.h>

void	get_cur_start_pos(t_line *line)
{
	char	answer[20];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(answer, 20);
	i = read(0, answer, 20);
	answer[i] = 0;
	i = 2;
	line->start.row = ft_atoi(answer + i);
	while (ft_isdigit(answer[i]))
		i++;
	line->start.col = ft_atoi(answer + i + 1);
}

void	match_hist(int key_pressed, t_line *line)
{
	int						i;
	static struct s_keyhist	keyhist[2] = {
		{KEY_UP, &old_hist_entry},
		{KEY_DOWN, &new_hist_entry}
	};

	i = 0;
	while (i < 2)
		if (key_pressed == keyhist[i++].key)
			keyhist[i - 1].p(line, &(line->hist));
}

void	match_move(int key_pressed, t_line *line)
{
	int						i;
	static struct s_keymove	keymove[8] = {
		{KEY_RIGHT, &cur_to_right},
		{KEY_LEFT, &cur_to_left},
		{KEY_HOME, &cur_to_home},
		{KEY_END, &cur_to_end},
		{KEY_SRIGHT, &next_word},
		{KEY_SLEFT, &prev_word},
		{KEY_SPREVIOUS, &prev_line},
		{KEY_SNEXT, &next_line}
	};

	i = 0;
	while (i < 8)
		if (key_pressed == keymove[i++].key)
			keymove[i - 1].p(line);
}

void	input_loop(t_line *line)
{
	int		key_pressed;

	while (42)
	{
		key_pressed = get_key();
		ft_getwinsz(&line->winsz);
		if (line->start.row + line->cur / line->winsz.col > line->winsz.row)
			line->start.row--;
		match_move(key_pressed, line);
		match_hist(key_pressed, line);
		if (key_pressed > 31 && key_pressed < 127)
			insert_char(line, key_pressed);
		if (key_pressed == KEY_DC || key_pressed == 127)
			delete_char(line, key_pressed);
		if (key_pressed == KEY_CTRLL)
		{
			tputs(tgoto(tgetstr("SF", NULL), 0, line->start.row - 1)
					, 1, &ft_putchar);
			line->start.row = 1;
			set_curpos(line);
		}
		if (key_pressed == '\n')
			break ;
	}
}

char	*line_editing(void)
{
	t_line	line;

	raw_terminal();
	ft_bzero(&line, sizeof(line));
	line.hist = retrieve_history();
	line.hist_size = ft_dlstsize(line.hist);
	get_cur_start_pos(&line);
	input_loop(&line);
	cur_to_end(&line);
	default_terminal();
	ft_putchar('\n');
	append_history(line.cmd);
	ft_dlstdelstr(&line.hist);
	return (ft_strdup(line.cmd));
}
