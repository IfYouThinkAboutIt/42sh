/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmdaba <rmdaba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 06:53:49 by rmdaba            #+#    #+#             */
/*   Updated: 2018/08/24 14:40:03 by rmdaba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include <sys/types.h>
#include <sys/uio.h>

static int	match_key(char *key_str, int i)
{
	static struct s_keymatch	key_couple[11] = {
		{CODE_UP, KEY_UP},
		{CODE_DO, KEY_DOWN},
		{CODE_RI, KEY_RIGHT},
		{CODE_LE, KEY_LEFT},
		{CODE_DEL, KEY_DC},
		{CODE_HOME, KEY_HOME},
		{CODE_END, KEY_END},
		{CODE_SRI, KEY_SRIGHT},
		{CODE_SLE, KEY_SLEFT},
		{CODE_SUP, KEY_SPREVIOUS},
		{CODE_SDO, KEY_SNEXT}
	};

	i = 0;
	while (i < 11)
		if (!ft_memcmp(key_couple[i++].key_code, key_str, MAX_KEY_LEN))
			return (key_couple[i - 1].key_ret);
	return (key_str[0]);
}

int			get_key(void)
{
	char	*key_str;
	int		key_pressed;

	key_str = ft_strnew(MAX_KEY_LEN);
	if (!key_str)
		return (-1);
	read(0, key_str, 1);
	if (*key_str == '\x1b')
		read(0, key_str + 1, MAX_KEY_LEN - 1);
	key_pressed = match_key(key_str, 0);
	free(key_str);
	return (key_pressed);
}
