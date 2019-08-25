/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ssl_Ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harssing <harssing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 18:54:19 by harssing          #+#    #+#             */
/*   Updated: 2019/08/23 16:38:43 by harssing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl_hd.h"

static void check_flags(t_node_st *fls, int ac, char **av)
{
    fls->idx = 2;
    fls->q = 0;
    fls->p = 0;
    fls->s = 0;
    fls->r = 0;
    while (fls->idx < ac)
    {
        if (!ft_strcmp("-q", av[fls->idx]))
            fls->q = 1;
        else if (!ft_strcmp("-p", av[fls->idx]))
            fls->p = 1;
        else if (!ft_strcmp("-r", av[fls->idx]))
            fls->r = 1;
        else if (!ft_strcmp("-s", av[fls->idx]))
        {
            fls->idx++;
            fls->s++;
        }
        else
            break;
        fls->idx++;
    }
    fls->fl_num = fls->idx - ac;
}

static void fl_no_rote(t_node_st *ssl, char **av)
{
    if (!ssl->q)
    {
        // if (!ft_strcmp(av[1], "sha256"))
        //     ft_printf("SHA256 (");
        // else 
        if (!ft_strcmp(av[1], "md5"))
            ft_printf("MD5 (");
        ft_printf("%s) = ", av[ssl->pars]);
    }
    // if (!ft_strcmp(av[1], "sha256"))
    //     do_sha256(ssl->c_stdin, ssl);
    // else
    if (!ft_strcmp(av[1], "md5"))
        do_md5(ssl->c_stdin, ssl);
    ft_putstr("\n");
}

static void fl_rote(t_node_st *ssl, char **av)
{
    if (not_file(ssl, av) == -1)
        return ;
    fstr(&ssl->c_stdin, ssl->fd);   //why / how ->fd is passed here?
    if (!ssl->r)
        fl_no_rote(ssl, av);
    else
    {
        // if (!ft_strcmp(av[1], "sha256"))
        //     do_sha256(ssl->c_stdin, ssl);
        // else
        if (!ft_strcmp(av[1], "md5"))
            do_md5(ssl->c_stdin, ssl);
        if (!ssl->q)
            ft_printf(" %s\n", av[ssl->pars]);
        else
            ft_printf("\n");      
    }
    free(ssl->c_stdin);
    close(ssl->fd);
    ssl->pars++;
}

static void  ft_ssl(t_node_st *ssl, int ac, char **av)
{
    check_flags(ssl, ac, av);
    if (ssl->p || (!ssl->fl_num && !ssl->s))    //If not files and not -s flag
    {
        fstr(&ssl->c_stdin, 0); //use stdin to read (0, e, 1);
        if (ssl->p && ssl->c_stdin)
            ft_printf("%s", ssl->c_stdin);  //testing

        // else                                //here
        // {                                      //here
        //     printf("%s\n", ssl->c_stdin);   //here
        //     exit (-1);                      //test area
        // }
        
        // if (!ft_strcmp(av[1], "sha256"))
        //     do_sha256(ssl->c_stdin, ssl);
        // else
        if (!ft_strcmp(av[1], "md5"))
            do_md5(ssl->c_stdin, ssl);
        ft_printf("\n");
        free(ssl->c_stdin);
    }
    ssl->pars = 2;
    while (ssl->pars < ac)
        if (print_fs(ssl, av, ac) == -1)
            break ;
    while (ssl->pars < ac)
        fl_rote(ssl, av);
}

int     main(int ac, char **av)
{
    t_node_st   ssl;

    if (ac == 1)
    {
        ft_printf("usage: ./ft_ssl [md5 | sha256] [ opts ]\n");
        exit(-1);
    }
    if (!ft_strcmp(av[1], "md5") || !(ft_strcmp(av[1], "sha256")))
        ft_ssl(&ssl, ac, av);
    else
    {
        ft_printf("ft_ssl: Error: '%s' is invalid. \n\n \
            usage: ./ft_ssl [md5 | sha256] [ opts ]\n", av[1]);
        exit(-1);
    }
    return (0);
}