#include "../includes/print_exit_status.h"

void	print_exit_status(t_info *info)
{
	ft_putnbr_fd(info->exit_status, 1);
	ft_putchar_fd('\n', 1);
}
