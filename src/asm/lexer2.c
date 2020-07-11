/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 12:52:10 by abosch            #+#    #+#             */
/*   Updated: 2020/07/11 14:25:44 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*token_new(t_token *tok, t_byte type, t_string *content)
{
	tok->type = type;
	tok->content = content;
	return (tok);
}

void			handle_labelarg(t_lexargs *args)
{
	t_token		tok;
	t_string	*str;
	int			i;

	i = ++(args->i);
	str = ft_string_init();
	while (ft_strchr(LABEL_CHARS, args->buf[i]) != NULL
		&& args->buf[i] != '\n')
	{
		if (args->buf[i] == '\0')
		{
			ft_string_append(str, args->buf + args->i);
			if (read_more(&i, args) == 0)
				return ;
		}
		else
			i++;
	}
	ft_string_nappend(str, args->buf + args->i, i);
	ft_list_push(args->toklist, ft_list_link_new(
				token_new(&tok, LABELARG, str), sizeof(t_token)));
	if (args->buf[i] == '\n')
		ft_list_push(args->toklist, ft_list_link_new(
					token_new(&tok, NEWLINE, NULL), sizeof(t_token)));
}

int				simple_case(t_lexargs *args)
{
	t_token		tok;
	char		c;

	c = args->buf[args->i];
	if ((c >= '\v' && c <= '\r') || c == ' ' || c == '\t')
		return (1);
	else if (c == ':') 
		handle_labelarg(args);
	else if (c == ',')
		ft_list_push(args->toklist, ft_list_link_new(
					token_new(&tok, SEP, NULL), sizeof(t_token)));
	else if (c == '%') 
		ft_list_push(args->toklist, ft_list_link_new(
					token_new(&tok, DIR, NULL), sizeof(t_token)));
	else if (c == '\n') 
		ft_list_push(args->toklist, ft_list_link_new(
					token_new(&tok, NEWLINE, NULL), sizeof(t_token)));
	else if (c == '.')
		ft_list_push(args->toklist, ft_list_link_new(
					token_new(&tok, DOT, NULL), sizeof(t_token)));
	else
		return (0);
	return (1);
}

void			handle_comment(t_lexargs *args)
{
	int			cnt;

	cnt = args->i; 
	while (args->buf[cnt] != '\n')
	{
		if (args->buf[cnt] == '\0')
		{
			if ((cnt = read(args->fd, args->buf, BUF_SIZE - 1)) == -1)
				ft_printerr("asm: handle_comment(read): %s\n", strerror(errno));
			else if (cnt == 0)
				return ;
			args->buf[cnt] = '\0';
			cnt = 0;
		}
		cnt++;
	}
	args->i = cnt;
}
