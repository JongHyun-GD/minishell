#include "minishell.h"

void handle_redirect(t_list *list, t_info *info)
{
	printf("info: %p\n", info);
	if (list->l_type != LTYPE_COMMAND)
		return;
	list = list->next;
	while (list)
	{
		if (list->l_type == LTYPE_PIPE)
		{
			// TODO: | 구현
			// handle_pipe();
		}
		if (list->l_type == LTYPE_REDIRECT_L)
		{
			// TODO: < 구현
			// handle_redirect_l();
		}
		if (list->l_type == LTYPE_REDIRECT2_L)
		{
			// TODO: << 구현
			// handle_redirect2_l();
		}
		if (list->l_type == LTYPE_REDIRECT_R)
		{
			// TODO: > 구현
			// handle_redirect_r();
		}
		if (list->l_type == LTYPE_REDIRECT2_R)
		{
			// TODO: >> 구현
			// handle_redirect2_r();
		}
		list = list->next;
	}
}
