/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:40:51 by abosch            #+#    #+#             */
/*   Updated: 2020/06/19 12:53:02 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*token_new(t_token *tok, t_byte type, char *content)
{
	tok->type = type;
	tok->content = content;
	return (tok);
}

void			lexer(t_list *toklist)
{
	char		buf[BUF_SIZE];
	int			ret;
	int			cnt;
	t_byte		no_nl;		
	t_token		tok;

	no_nl = 0;
	while ((ret = read(0, buf, BUF_SIZE - 1)) > 0)
	{
		buf[ret] = '\0';
		cnt = -1;
		while (buf[++cnt] != '\0' && buf[cnt] != '#')
		{
			if (ft_isspace(buf[cnt]))
				continue ;
			else if (buf[cnt] == ':') 
				ft_list_push(toklist, ft_list_link_new(
							token_new(&tok, LSEP, NULL), sizeof(t_token)));
			else if (buf[cnt] == ',')
				ft_list_push(toklist, ft_list_link_new(
							token_new(&tok, SEP, NULL), sizeof(t_token)));
			else if (buf[cnt] == '%') 
				ft_list_push(toklist, ft_list_link_new(
							token_new(&tok, IND, NULL), sizeof(t_token)));
			else if (buf[cnt] == '\n') 
				ft_list_push(toklist, ft_list_link_new(
							token_new(&tok, NEWLINE, NULL), sizeof(t_token)));
			else if (buf[cnt] == '#' || no_nl)
			{
				while (buf[cnt] != '\n' && buf[cnt] != '\0')
					++cnt;
				if (buf[cnt] == '\0')
					no_nl = 1;
			}
		}
	}
	if (ret == -1)
		ft_printerr("asm: lexer(read): %s\n", strerror(errno));
}
