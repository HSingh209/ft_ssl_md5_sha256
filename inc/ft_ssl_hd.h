/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_hd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harssing <harssing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:37:26 by harssing          #+#    #+#             */
/*   Updated: 2019/08/23 13:02:57 by harssing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_HD_H
#define FT_SSL_HD_H
#include "../libft/assets/ft_printf/ft_hprintf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

# ifndef MAX_INPUT
# define  MAX_INPUT 10
# endif
// # define A 0
// # define B 1
// # define C 2
// # define D 3
# define LEFTROT(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
# define F(B, C, D) ((B) & (C)) | (~(B) & (D))
# define G(B, C, D) ((B) & (D)) | ((C) & ~(D))
# define H(B, C, D) (B) ^ (C) ^ (D)
# define I(B, C, D) (C) ^ (B | ~(D))

static const uint32_t	(g_r[64]) =
{	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t	(g_k[64]) =
{	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

/* fn -> filename */
/*  */
typedef struct  s_md5s
{
        uint32_t        bit_len;
        uint32_t        bytes_l;
        uint32_t        buff[8];
}               t_md5s;

typedef  struct  s_node_st
{
        char        *c_stdin;
		char			*bytes;
        int         output;
        int         md5;
        int         sha256;
        // char        **fn;               
        char        **in_qu;
        uint32_t    *fl_size;
		int			idx;
		int			fl_num;	//Where the files start in (av)
        int         size;	//Using size in place of the len int.
		int			fd;
		int			str;	//where / how is this setup?
		int		pars;
	    int     p;
        int     q;
        int     r;
        int     s;
		uint32_t	*t;
		uint32_t	temp;
		uint32_t	a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
		uint32_t		h0;
		uint32_t		h1;
		uint32_t		h2;
		uint32_t		h3;
		uint32_t		h4;
		uint32_t		h5;
		uint32_t		h6;
		uint32_t		h7;
        uint32_t     h;

}                   t_node_st; 

char 	*ft_itoa_base_ssl(uint32_t num, int base);
void	do_md5(char *stin, t_node_st *blc);
void 	fstr(char **st_in, int fd);
int    md5_algo(unsigned char *msg, int len, t_node_st *ssl);
int     not_file(t_node_st *infos, char **av);
char*    padd_zero(char *str);
uint32_t	swap_int32(const uint32_t value);
int		print_fs(t_node_st *fin, char **av, int ac);


#endif