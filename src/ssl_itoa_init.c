/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_itoa_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harssing <harssing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 19:23:26 by harssing          #+#    #+#             */
/*   Updated: 2019/08/22 20:56:59 by harssing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl_hd.h"

char    *padd_zero(char  *str)
{
    int i;

    i = ft_strlen(str);
    while (i++ < 8)
    {
        ft_printf("0");
    }
    return (str);
}

void set_block(t_node_st *node)
{
    node->h0 = 0x67452301;
	node->h1 = 0xefcdab89;
	node->h2 = 0x98badcfe;
	node->h3 = 0x10325476;
}

static int  ft_get_len(uint32_t num, int base)
{
    int i;

    i = 0;
    while (num)
    {
        num /= base;
        i++;
    }
    return (i);
}

static char *free_str(char *digest)
{
    char    *temp;

    temp = digest;
    digest = ft_strsub(digest, 1, ft_strlen(digest) - 1);
    free(temp);
    return (digest);
}

char *ft_itoa_base_ssl(uint32_t num, int base)
{
   // int i;
    int len;
    char    *str;
    char    *tab;

    tab = "0123456789abcdef";
    len = ft_get_len(num, base);
    if (num == 0)
        return (ft_strdup("0"));
    if (!(str = malloc(sizeof(char) * (len + 1))))
        return (NULL);
    str[len + 1] = 0;
    while (len + 1)
    {
        str[len] = tab[num % base];
        num = num / base;
        len--;
    }
    if (str[0] == '0')
        str = free_str(str);
    return (str);
}

int     not_file(t_node_st *infos, char **av)
{
    if ((infos->fd = open(av[infos->pars], O_RDWR)) < 0)
    {
        if (!ft_strcmp(av[1], "sha256"))
            ft_printf("ft_ssl: sha256 \n");
        if (!ft_strcmp(av[1], "md5"))
            ft_printf("ft_ssl: md5 \n");
        ft_putstr(av[infos->pars]);
        ft_printf(": No such file / directory\n");
        infos->pars++;
        return (-1);
    }
    return (0);
}
