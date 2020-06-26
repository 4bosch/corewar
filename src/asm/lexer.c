/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:40:51 by abosch            #+#    #+#             */
/*   Updated: 2020/06/26 16:39:38 by abosch           ###   ########.fr       */
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
	else if (c == '.')
		ft_list_push(toklist, ft_list_link_new(
					token_new(&tok, DOT, NULL), sizeof(t_token)));
	else
		return (0);
	return (1);
}

static void		last_append(t_string *str, char *buf, int *begin, int i)
{
	char		c;

	c = buf[i];
	buf[i] = '\0';
	ft_string_append(str, buf + *begin);
	buf[i] = c;
}

void			handle_symbol(t_list *toklist, char *buf, int *begin, int fd)
{
	t_token		tok;
	t_string	*str;
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
				ft_printerr(EREADSYM, strerror(errno));
			buf[i] = '\0';
			*begin = 0;
			i = 0;
		}
		else
			i++;
	}
	last_append(str, buf, begin, i);
	*begin = i - 1;
	ft_list_push(toklist, ft_list_link_new(token_new(&tok, SYMBOL, str),
				sizeof(t_token)));
}

void			handle_string(t_list *toklist, char *buf, int *begin, int fd)
{
	t_token		tok;
	t_string	*str;
	int			i;

	i = *begin;
	str = ft_string_init();
	while (buf[i] != '"')
	{
		if (buf[i] == '\0')
		{
			ft_string_append(str, buf + *begin);
			if ((i = read(fd, buf, BUF_SIZE - 1)) == 0)
				ft_printerr(ENCQ);
			else if (i == -1)
				ft_printerr(EREADSTR, strerror(errno));
			buf[i] = '\0';
			*begin = 0;
			i = 0;
		}
		else
			i++;
	}
	last_append(str, buf, begin, i);
	*begin = i;
	ft_list_push(toklist, ft_list_link_new(token_new(&tok, STRING, str),
				sizeof(t_token)));
}

void			handle_comment(char *buf, int *i, int fd)
{
	int			cnt;

	cnt = *i; 
	while (buf[cnt] != '\n')
	{
		if (buf[cnt] == '\0')
		{
			if ((cnt = read(fd, buf, BUF_SIZE - 1)) == -1)
				ft_printerr(EREADCOM, strerror(errno));
			else if (cnt == 0)
				return ;
			buf[cnt] = '\0';
			cnt = 0;
		}
		cnt++;
	}
	*i = cnt;
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
			if (simple_case(toklist, buf[i]))
				continue ;
			else if (buf[i] == '#')
				handle_comment(buf, &i, 0);
			else if (buf[i] == '"')
			{
				++i;
				handle_string(toklist, buf, &i, 0);
			}
			else if (ft_strchr(LABEL_CHARS, buf[i]) != NULL)
				handle_symbol(toklist, buf, &i, 0);
			else
				ft_printerr(EIC, buf[i]);
	}
	if (i == -1)
		ft_printerr(EREADLEX, strerror(errno));
}
