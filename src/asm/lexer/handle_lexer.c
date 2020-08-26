#include "lexer.h"

static void		create_symbol_token(t_string *str, int i,
	t_lexargs *args, t_list *label)
{
	t_label	lab;

	if (args->buf[i] == ':')
	{
		if (str->buf[0] == '+' || str->buf[0] == '-')
			ft_printerr("asm: Label begin with an illegal "
				"character : %c.\n", args->buf[i]);
		args->i = i;
		ft_list_push(args->toklist, token_new(LABELDEF, str));
		ft_list_push(label, ft_list_link_new(
			new_label(str->buf, &lab), sizeof(t_label)));
	}
	else
	{
		args->i = i - 1;
		ft_list_push(args->toklist, token_new(SYMBOL, str));
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
	t_string	*str;
	int			i;

	i = args->i++ - 1;
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
	ft_list_push(args->toklist, token_new(STRING, str));
}

void			handle_labelarg(t_lexargs *args)
{
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
	ft_string_nappend(str, args->buf + args->i, i - args->i);
	args->i = i - 1;
	ft_list_push(args->toklist, token_new(LABELARG, str));
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
	ft_list_push(args->toklist, token_new(NEWLINE, NULL));
}
