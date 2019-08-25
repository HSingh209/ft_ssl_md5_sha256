/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_md5_dig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harssing <harssing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 16:40:22 by harssing          #+#    #+#             */
/*   Updated: 2019/08/23 17:10:18 by harssing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl_hd.h"

uint32_t	swap_int32(const uint32_t value)
{
	uint32_t result;

	result = 0;
	result |= (value & 0x000000FF) << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= (value & 0xFF000000) >> 24;
	return (result);
}

void	rotate(t_node_st *ssln, char **av)
{
	if (!ft_strcmp(av[1], "md5"))
	{
		if (!ssln->q)
			(!ssln->r) ? ft_printf("MD5 (\"%s\") = ", av[ssln->pars])
			 : 0;
		do_md5(av[ssln->pars], ssln);
	}
	if (!ssln->q && ssln->r)
		ft_printf(" \"%s\"\n", av[ssln->pars]);
	else
		ft_printf("\n");
	
}

void	no_rotate(t_node_st *ssln, char **av)
{
	if (!ssln->q)
	{
		if (!ft_strcmp(av[1], "md5"))
			ft_printf("MD5 (\"");
		ft_putstr(av[ssln->pars]);
		ft_printf("\") = ");
	}
	if (!ft_strcmp(av[1], "md5"))
		do_md5(av[ssln->pars], ssln);
	ft_printf("\n");
}

int		print_fs(t_node_st *fin, char **av, int ac)
{
	if (!ft_strcmp("-p", av[fin->pars]))
		fin->p = 1;
	else if (!ft_strcmp("-q", av[fin->pars]))
		fin->q = 1;
	else if (!ft_strcmp("-r", av[fin->pars]))
		fin->r = 1;
	else if (!ft_strcmp("-s", av[fin->pars]))
	{
		fin->pars++;
		if (fin->pars < ac)
		{
			if (!fin->r)
				no_rotate(fin, av);
			else
				rotate(fin, av);
		}
	}
	else
		return (-1);
	fin->pars++;
	return (0);
}
