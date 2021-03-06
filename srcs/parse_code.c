/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:19:16 by mellie            #+#    #+#             */
/*   Updated: 2021/01/21 21:49:23 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// int validate_magic(unsigned char *bytes)
// {
//     unsigned char   magic[4];
//     int             i;
//     if (bytes == NULL)
//         return (0);
//     i = 0;
//     while (i < 4)
//     {
//         magic[i] = COREWAR_EXEC_MAGIC >> ((3 - i) * 8) & 0b11111111;
//         if (magic[i] != *bytes)
//             return (0);
//         i++;
//         bytes++;
//     }
//     return (1);
// }
void			check_magic_header(unsigned char *p)
{
	int				tmp;
	unsigned char	*m;
	int				i;

	tmp = COREWAR_EXEC_MAGIC;
	m = (unsigned char *)&tmp + 3;
	i = 0;
	while (i < 4)
	{
		if (*p == *m)
		{
			p++;
			m--;
			i++;
		}
		else
			terminate(ERR_3_READING_FAILED);
	}
}

void			check_null_octet(unsigned char *p)
{
	if (ft_memcmp(p, "\0\0\0\0", 4))
		terminate(ERR_3_READING_FAILED);
}

unsigned int	check_code_size(unsigned char *p)
{
	unsigned int	tmp;
	unsigned char	*dst;
	int				i;

	tmp = 0;
	dst = (unsigned char *)&tmp + 3;
	i = 0;
	while (i < 4)
	{
		*dst = *p;
		p++;
		dst--;
		i++;
	}
	if (tmp > CHAMP_MAX_SIZE)
		terminate(ERR_4_CODE_MAXSIZE);
	return (tmp);
}

void			read_code(unsigned char *p, t_cor *f, t_player **player)
{
	check_null_octet((p += COMMENT_LENGTH));
	f->bsize = lseek(f->fd, 0L, SEEK_END);
	f->bsize -= f->offset;
	if (f->bsize != (*player)->size)
		terminate(ERR_5_INV_CODESIZE);
	(*player)->code = (unsigned char *)malloc(f->bsize + 1);
	err_allocate((*player)->code);
	ft_bzero((*player)->code, f->bsize + 1);
	f->offset = lseek(f->fd, -(long)(f->bsize), SEEK_END);
	if ((f->offset = read(f->fd, (*player)->code, f->bsize)) != f->bsize)
		terminate(ERR_3_READING_FAILED);
	close(f->fd);
}

void			parse_code(char *av, t_player **player)
{
	// + 4 bytes			magic header COREWAR_EXEC_MAGIC
	// + PROG_NAME_LENGTH	champ name 128 bytes
	// + 4 bytes			4 NULL octets
	// + 4 bytes			code size CHAMP_MAX_SIZE 2867789673
	// + COMMENT_LENGTH	Champion comment
	// + 4 bytes			4 NULL octets
	// + N bytes			code
	t_cor			f;
	unsigned char	header[17 + PROG_NAME_LENGTH + COMMENT_LENGTH];
	unsigned char	*p;

	if ((f.fd = open(av, O_RDONLY, 0)) <= 0)
		terminate(ERR_3_READING_FAILED);
	f.bsize = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	if ((f.offset = read(f.fd, &header, f.bsize)) != f.bsize)
		terminate(ERR_3_READING_FAILED);
	header[f.offset] = '\0';
	p = header;
	check_magic_header(p);
	(*player)->name = (char *)malloc(PROG_NAME_LENGTH + 1);
	err_allocate((*player)->name);
	p += 4;
	(*player)->name[PROG_NAME_LENGTH] = '\0';
	(*player)->name = ft_memcpy((*player)->name, p, PROG_NAME_LENGTH);
	check_null_octet((p += PROG_NAME_LENGTH));
	(*player)->size = check_code_size((p += 4));
	(*player)->comment = (char *)malloc(COMMENT_LENGTH + 1);
	err_allocate((*player)->comment);
	p += 4;
	(*player)->comment[COMMENT_LENGTH] = '\0';
	(*player)->comment = ft_memcpy((*player)->comment, p, COMMENT_LENGTH);
	read_code(p, &f, player);
}
