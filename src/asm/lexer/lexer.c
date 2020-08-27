/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:18:20 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 14:18:22 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include "debug.h" ///////////////DELETE

int				read_more(int *i, t_lexargs *args)
{
	if ((*i = read(args->fd, args->buf, BUF_SIZE - 1)) == 0)
		return (0);
	else if (*i == -1)
		ft_printerr("asm : read_more(read): %s\n", strerror(errno));
	args->buf[*i] = '\0';
	args->i = 0;
	*i = 0;
	return (1);
}

t_list_link		*token_new(t_byte type, t_string *content)
{
	t_token	tok;

	tok.type = type;
	tok.content = content;
	return (ft_list_link_new(&tok, sizeof(t_token)));
}

static int		simple_case(t_lexargs *args)
{
	char		c;

	c = args->buf[args->i];
	if ((c >= '\v' && c <= '\r') || c == ' ' || c == '\t')
		return (1);
	else if (c == ':')
		handle_labelarg(args);
	else if (c == ',')
		ft_list_push(args->toklist, token_new(SEP, NULL));
	else if (c == '%')
	{
		if (args->buf[args->i + 1] == ' ')
			ft_printerr("asm: There is a space after a direct "
				"character ('%c').\n", DIRECT_CHA);
		ft_list_push(args->toklist, token_new(DIR, NULL));
	}
	else if (c == '\n')
		ft_list_push(args->toklist, token_new(NEWLINE, NULL));
	else if (c == '.')
		ft_list_push(args->toklist, token_new(DOT, NULL));
	else
		return (0);
	return (1);
}

static void		lex_forest(t_lexargs *args, t_list *label)
{
	if (simple_case(args))
		return ;
	else if (args->buf[args->i] == '#')
		handle_comment(args);
	else if (args->buf[args->i] == '"')
		handle_string(args);
	else if (ft_strchr(LABEL_CHARS, args->buf[args->i]) != NULL
		|| ft_strchr("+-", args->buf[args->i]) != NULL)
		handle_symbol(args, label);
	else
		ft_printerr(EIC, args->buf[args->i]);
}

void			lexer(t_list *toklist, t_list *label, int fd)
{
	char		buf[BUF_SIZE];
	t_lexargs	args;

	args.fd = fd;
	args.toklist = toklist;
	args.buf = buf;
	while ((args.i = read(fd, buf, BUF_SIZE - 1)) > 0)
	{
		buf[args.i] = '\0';
		args.i = -1;
		while (buf[++args.i] != '\0')
			lex_forest(&args, label);
	}
	if (args.i == -1)
		ft_printerr("asm: lexer(read): %s\n", strerror(errno));
	if (((t_token*)toklist->head->prev->content)->type != NEWLINE)
		ft_printerr(ENOLASTNL);
}
