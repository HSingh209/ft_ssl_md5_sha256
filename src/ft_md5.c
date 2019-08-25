/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harssing <harssing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:55:55 by harssing          #+#    #+#             */
/*   Updated: 2019/08/23 16:49:47 by harssing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl_hd.h"

static void set_block(t_node_st *node)
{
    node->h0 = 0x67452301;
	node->h1 = 0xefcdab89;
	node->h2 = 0x98badcfe;
	node->h3 = 0x10325476;
}

static int pad_md5(unsigned char *stin, int len, t_node_st *node)
{
    int i;

    i = 0;
    set_block(node);
    node->size = len + 1;
    while (node->size % 64 != 56)
        node->size++;
    if (!(node->bytes = malloc(node->size + 64)))
        return (-1);
    //node->bytes = (ft_bzero(node->bytes, node->size + 64));//type conflict char* vs void
    while (i < node->size + 64)
        node->bytes[i++] = '\0';
    ft_strcpy((char*)node->bytes, (const char *)stin);
    *(uint32_t*)(node->bytes + len) = 0x80;
    *(uint32_t*)(node->bytes + node->size) = (uint32_t)(8 * len);
    node->str = 0;
    return (0);
}

static void fig_hash(t_node_st *fs, int i)
{
    if (i < 16)
    {
        fs->f = F(fs->b, fs->c, fs->d);
        fs->g = i;
    }
    else if (i < 32)
    {
        fs->f = G(fs->b, fs->c, fs->d);
        fs->g = (5 * i + 1) % 16;
    }
    else if (i < 48)
    {
        fs->f = H(fs->b, fs->c, fs->d);
        fs->g = (3 * i + 5) % 16;
    }
    else
    {
        fs->f = I(fs->b, fs->c, fs->d);
        fs->g = (7 * i) % 16;
    }
    fs->temp = fs->d;
    fs->d = fs->c;
    fs->c = fs->b;
    fs->b = fs->b + LEFTROT((fs->a + fs->f + g_k[i] + fs->t[fs->g]), g_r[i]);
    fs->a = fs->temp;
}

void fstr(char **st_in, int fd)
{
    char        e[2];
    int         read_f;
    // uint32_t    tot_fls;
    char        *buff;
    char        *temp;

    e[1] = 0;
    read_f = 1;
    buff = ft_strdup("");
        // printf("%s\n", buff);
        //     printf("%d\n", read_f);
    while (read_f > 0)
    {
        
        read_f = read(fd, e, 1);
        if (read_f == 0)
            break;
        temp = buff;
        buff = ft_strjoin(buff, e);
        // tot_fls += read_f;
        free(temp);
    }
    st_in[0] = buff;
}

int    md5_algo(unsigned char *msg, int len, t_node_st *ssl)
{
    int i;

    if (pad_md5(msg, len, ssl) == -1)
        return (-1);
    while (ssl->str < ssl->size)
    {
        ssl->t = (uint32_t *)(ssl->bytes + ssl->str);
        ssl->a = ssl->h0;
        ssl->b = ssl->h1;
        ssl->c = ssl->h2;
        ssl->d = ssl->h3;
        i = -1;
        while (++i < 64)
            fig_hash(ssl, i);
        ssl->h0 += ssl->a;
        ssl->h1 += ssl->b;
        ssl->h2 += ssl->c;
        ssl->h3 += ssl->d;
        ssl->str += 64;
    }
    free(ssl->bytes);
    return (0);
}

void    do_md5(char *stin, t_node_st *blc)
{
    char    *tmp;

    if (md5_algo((uint8_t *)stin, ft_strlen(stin), blc) == -1)
        return ;
    tmp = ft_itoa_base_ssl(swap_int32(blc->h0), 16);
    padd_zero(tmp);
    ft_putstr(tmp);
    free(tmp);
    tmp = ft_itoa_base_ssl(swap_int32(blc->h1), 16);
    padd_zero(tmp);
    ft_putstr(tmp);
    free(tmp);
    tmp = ft_itoa_base_ssl(swap_int32(blc->h2), 16);
    padd_zero(tmp);
    ft_putstr(tmp);
    free(tmp);
    tmp = ft_itoa_base_ssl(swap_int32(blc->h3), 16);
    padd_zero(tmp);
    ft_putstr(tmp);
    free(tmp);
}