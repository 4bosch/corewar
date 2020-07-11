/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:24:13 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/11 14:01:53 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "parser.h"

#include "debug.h"

#include <stdlib.h>

static int	print_token(void *content, size_t content_size, unsigned position, unsigned total)
{
	t_token *tok;

	tok = (t_token*)content;
	ft_printf("| ");
	if (tok->type == LABELDEF)
		ft_printf("Label def|");
	else if (tok->type == SEP)
		ft_printf(",        |");
	else if (tok->type == DIR)
		ft_printf("%%        |");
	else if (tok->type == SYMBOL)
		ft_printf("Symbol   |");
	else if (tok->type == NEWLINE)
		ft_printf("Newline  |");
	else if (tok->type == DOT)
		ft_printf(".        |");
	else if (tok->type == STRING)
		ft_printf("String   |");
	else if (tok->type == LABELARG)
		ft_printf("Label arg|");
	if (tok->content != NULL)
		ft_printf(" %s |\n", tok->content->buf);
	else
		ft_printf("    |\n");
	return (1);
}

void		print_tab(t_list **tab)
{
	int		i;

	i = -1;
	while (tab[++i] != NULL)
	{
		ft_printf("=====================================================\n");
		ft_list_print(tab[i], &print_token);
		ft_printf("=====================================================\n\n");
	}
}

static int	ft_list_count(t_list *list)
{
	t_list_link		*link;
	unsigned int	cnt;
	int				i;

	cnt = -1;
	i = 0;
	link = list->head;
	while (++cnt < list->len)
	{
		if (((t_token*)link->content)->type == NEWLINE)
			i++;
		link = link->next;
	}
	return (i);
}

static void	init_tab(int len, t_list **tab)
{
	int	i;

	i = -1;
	while (++i < len)
		if ((tab[i] = ft_list_init()) == NULL)
			ft_printerr("asm: init_tab(ft_list_init): %s\n", strerror(errno));
	tab[len] = NULL;
}

static void	fill_tab(int len, t_list **tab, t_list *list)
{
	t_list_link		*link;
	int				j;

	init_tab(len, tab);
	j = 0;
	link = list->head;
	while (link->next != list->head)
	{
		if (((t_token*)link->content)->type != NEWLINE)
		{
			link = link->next;
			ft_list_push(tab[j], ft_list_pop_front(list));
		}
		else
		{
			link = link->next;
			ft_list_push(tab[j], ft_list_pop_front(list));
			j++;
		}
	}
	ft_list_push(tab[j], ft_list_pop_front(list));
	if (((t_token*)tab[j - 1]->head->prev->content)->type != NEWLINE)
		ft_printerr(ENOLASTNL);
}

t_list		**list2tab(t_list *token_list)
{
	t_list	**ret;
	int		len;

	if ((len = ft_list_count(token_list)) == 0)
		ft_printerr(ENONL);
	if ((ret = (t_list**)malloc(sizeof(t_list*) * (len + 1))) == NULL)
		ft_printerr("asm: list2tab(malloc): %s\n", strerror(errno));
	fill_tab(len, ret, token_list);
	return (ret);
}

int			asmcore(int ac, char **av)
{
	t_list	*token_list;
	t_list	**token_tab;
	t_list	*label;
	t_cmd	cmd;

	if ((token_list = ft_list_init()) == NULL)
		ft_printerr("asm: asmcore(ft_list_init): %s\n", strerror(errno));
	lexer(token_list);
	ft_list_print(token_list, &print_token); //DELETE
	token_tab = list2tab(token_list);
	print_tab(token_tab); //DELETE
	if ((label = ft_list_init()) == NULL)
		ft_printerr("asm: asmcore(ft_list_init): %s\n", strerror(errno));
	ft_bzero(&cmd, sizeof(t_cmd));
	parser(token_tab, label, &cmd);
	//DEBUG
//	ft_printf("name : |%s|\ncomment : |%s|\n", cmd.name, cmd.comment);
//	ft_printf("%s\n",label->head->content);
//	ft_printf("%s\n",label->head->next->content);
	//END
	return (EXIT_SUCCESS);
}
