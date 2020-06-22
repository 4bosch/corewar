/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:40:51 by abosch            #+#    #+#             */
/*   Updated: 2020/06/22 18:43:28 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include "debug.h" ///////////////DELETE

static t_token	*token_new(t_token *tok, t_byte type, t_string *content)
{
	tok->type = type;
	tok->content = content;
	return (tok);
}

static int		simple_case(t_list *toklist, char c)
{
	t_token		tok;

	if ((c >= '\v' && c <= '\r') || c == ' ' || c == '\t')
		return (1);
	else if (c == ':') 
		ft_list_push(toklist, ft_list_link_new(
					token_new(&tok, LSEP, NULL), sizeof(t_token)));
	else if (c == ',')
		ft_list_push(toklist, ft_list_link_new(
					token_new(&tok, SEP, NULL), sizeof(t_token)));
	else if (c == '%') 
		ft_list_push(toklist, ft_list_link_new(
					token_new(&tok, IND, NULL), sizeof(t_token)));
	else if (c == '\n') 
		ft_list_push(toklist, ft_list_link_new(
					token_new(&tok, NEWLINE, NULL), sizeof(t_token)));
	else
		return (0);
	return (1);
}

void			handle_symbol(t_list *toklist, char *buf, int *begin, int fd)
{
	t_token		tok;
	t_string	*str;
	char		c;
	int			i;

	i = *begin;
	str = ft_string_init();
	while (ft_strchr(LABEL_CHARS, buf[i]) != NULL && buf[i] != '\n')
	{
		if (buf[i] == '\0')
		{
			ft_string_append(str, buf + *begin);
			if ((i = read(fd, buf, BUF_SIZE - 1)) == 0)
				return ;
			else if (i == -1)
				ft_printerr("asm: handle_symbol(read): %s\n", strerror(errno));
			buf[i] = '\0';
			i = 0;
			*begin = 0;
		}
		else
			i++;
	}
	c = buf[i];
	buf[i] = '\0';
	ft_string_append(str, buf + *begin);
	buf[i] = c;
	ft_list_push(toklist, ft_list_link_new(token_new(&tok, SYMBOL, str),
		sizeof(t_token)));
	*begin = i - 1;
}

static int		is_newline(int c)
{
	return ((c != '\n') ? 1 : 0);
}

void			handle_comment(char *buf, int *i, int fd)
{
	while (buf[*i] != '\n')
	{
		*i += ft_strskip(buf + *i, &is_newline);
		if (buf[*i] == '\0')
		{
			if ((*i = read(fd, buf, BUF_SIZE - 1)) == -1)
				ft_printerr("asm: handle_comment(read): %s\n", strerror(errno));
			else if (*i == 0)
				return ;
			buf[*i] = '\0';
			*i = 0;
		}
	}
}

void			lexer(t_list *toklist)
{
	char		buf[BUF_SIZE];
	int			i;

	while ((i = read(0, buf, BUF_SIZE - 1)) > 0)
	{
		buf[i] = '\0';
		i = -1;
		while (buf[++i] != '\0' && buf[i] != '#')
		{
			if (simple_case(toklist, buf[i]))
				continue ;
			else if (buf[i] == '#')
				handle_comment(buf, &i, 0);
			else if (ft_strchr(LABEL_CHARS, buf[i]) != NULL)
				handle_symbol(toklist, buf, &i, 0);
		}
	}
	if (i == -1)
		ft_printerr("asm: lexer(read): %s\n", strerror(errno));
}
