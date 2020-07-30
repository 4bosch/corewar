/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:40:51 by abosch            #+#    #+#             */
/*   Updated: 2020/07/27 15:53:46 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include "debug.h" ///////////////DELETE

int				read_more(int *i, t_lexargs *args)
{
	if ((*i = read(args->fd, args->buf, BUF_SIZE - 1)) == 0)
		return (0);
	else if (*i == -1)
		ft_printerr("asm : read_more(read): %s\n",strerror(errno));
	args->buf[*i] = '\0';
	args->i = 0;
	*i = 0;
	return (1);
}

static void		create_symbol_token(t_string *str, int i, t_lexargs *args, t_list *label)
{
	t_token tok;
	t_label	lab;

	if (args->buf[i] == ':')
	{
		if (str->buf[0] == '+' || str->buf[0] == '-')
			ft_printerr("asm: Label begin with an illegal character : %c.\n", args->buf[i]);
		args->i = i;
		ft_list_push(args->toklist, ft_list_link_new(token_new(&tok, LABELDEF, str),
					sizeof(t_token)));
		ft_list_push(label, ft_list_link_new(
			new_label(tok.content->buf, &lab), sizeof(t_label)));
	}
	else
	{
		args->i = i - 1;
		ft_list_push(args->toklist, ft_list_link_new(token_new(&tok, SYMBOL, str),
					sizeof(t_token)));
	}
}

void			handle_symbol(t_lexargs *args, t_list *label)
{
	t_string	*str;
	int			i;

	i = args->i;
	str = ft_string_init();
	if (args->buf[i] == '-' || args->buf[i] == '+')
		++i;
	while (ft_strchr(LABEL_CHARS, args->buf[i]) != NULL
		&& args->buf[i] != '\n' && args->buf[i] != ':')
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
	ft_string_nappend(str, args->buf + args->i, i - args->i);
	create_symbol_token(str, i, args, label);
}

void			handle_string(t_lexargs *args)
{
	t_token		tok;
	t_string	*str;
	int			i;

	i = args->i - 1;
	str = ft_string_init();
	while (args->buf[++i] != '"')
	{
		if (args->buf[i] == '\0')
		{
			ft_string_append(str, args->buf + args->i);
			if (read_more(&i, args) == 0)
				return ;
		}
	}
	ft_string_nappend(str, args->buf + args->i, i - args->i);
	args->i = i;
	ft_list_push(args->toklist, ft_list_link_new(token_new(&tok, STRING, str),
				sizeof(t_token)));
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
			if (simple_case(&args))
				continue ;
			else if (buf[args.i] == '#')
				handle_comment(&args);
			else if (buf[args.i] == '"')
			{
				++args.i;
				handle_string(&args);
			}
			else if (ft_strchr(LABEL_CHARS, buf[args.i]) != NULL
				|| ft_strchr("+-" ,buf[args.i]) != NULL)
				handle_symbol(&args, label);
			else
				ft_printerr(EIC, buf[args.i]);
	}
	if (args.i == -1)
		ft_printerr("asm: lexer(read): %s\n", strerror(errno));
}
