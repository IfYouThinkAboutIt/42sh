/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmdaba <rmdaba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 06:53:45 by rmdaba            #+#    #+#             */
/*   Updated: 2018/08/22 11:07:15 by rmdaba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	default_terminal(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}

void	raw_terminal(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_oflag &= ~(OPOST);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
	tgetent(NULL, getenv("TERM"));
}

int		ft_getwinsz(t_winsz *winsz)
{
	struct winsize	w;

	if (ioctl(0, TIOCGWINSZ, &w))
		return (1);
	winsz->col = w.ws_col;
	winsz->row = w.ws_row;
	return (0);
}

void	insert_char(t_line *line, int key)
{
	if (line->length + 1 >= MAX_CMD_LEN)
		return ;
	ft_memmove(line->cmd + line->cur + 1, line->cmd + line->cur,
			MAX_CMD_LEN - line->cur - 1);
	line->cmd[line->cur] = key;
	line->length++;
	line->cur++;
	tputs(tgetstr("im", NULL), 1, &ft_putchar);
	ft_putchar_fd(key, 0);
	tputs(tgetstr("ei", NULL), 1, &ft_putchar);
}

void	delete_char(t_line *line, int key)
{
	if (key == 127 && !line->cur)
		return ;
	if (key == 127)
		cur_to_left(line);
	if (line->cur == line->length)
		return ;
	ft_memmove(line->cmd + line->cur, line->cmd + line->cur + 1,
			MAX_CMD_LEN - line->cur - 1);
	line->length--;
	tputs(tgetstr("cd", NULL), 0, &ft_putchar);
	ft_putstr_fd(line->cmd + line->cur, 0);
	set_curpos(line);
}
