/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:19:16 by mellie            #+#    #+#             */
/*   Updated: 2021/01/12 23:34:37 by mellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int validate_magic(unsigned char *bytes)
{
    unsigned char   magic[4];
    int             i;
    if (bytes == NULL)
        return (0);
    i = 0;
    while (i < 4)
    {
        magic[i] = COREWAR_EXEC_MAGIC >> ((3 - i) * 8) & 0b11111111;
        if (magic[i] != *bytes)
            return (0);
        i++;
        bytes++;
    }
    return (1);
}
void	check_magic_header(unsigned char *p)
{
	int tmp;

	tmp = COREWAR_EXEC_MAGIC;
	if (ft_memcmp(p, &tmp, 4))
		terminate(ERR_3_READING_FAILED);
}

void	check_null_octet(unsigned char *p)
{
	if (ft_memcmp(p, 0000, 4))
		terminate(ERR_3_READING_FAILED);
}

void	check_code_size(unsigned char *p)
{
	int tmp;
	
	ft_memcpy(&tmp, p, 4);
}

void	parse_code(char *av, t_player **player)
{
    /*
    + 4 bytes			magic header COREWAR_EXEC_MAGIC
    + PROG_NAME_LENGTH	champ name 128 bytes
	+ 4 bytes			4 NULL octets
	+ 4 bytes			code size CHAMP_MAX_SIZE
	+ COMMENT_LENGTH	Champion comment
	+ 4 bytes			4 NULL octets
	+ N bytes			code
    */
    int fd;
	int hsize;
	int offset;
	unsigned char header[17 + PROG_NAME_LENGTH + COMMENT_LENGTH];
	unsigned char *p;

    if ((fd = open(av, O_RDONLY,0)) <= 0)
        terminate(ERR_3_READING_FAILED);
    hsize = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	if ((offset = read(fd, &header, hsize)) != hsize)
		terminate(ERR_3_READING_FAILED);
	header[offset] = '\0';
	p = header;
	validate_magic(p);
	//check_magic_header(p);
	(*player)->name = (char *)malloc(sizeof(char) * (PROG_NAME_LENGTH + 1));
	err_allocate((*player)->name);
	p += 4;
	(*player)->name[PROG_NAME_LENGTH] = '\0';
	(*player)->name = ft_strncpy((*player)->name, (const char *)p, PROG_NAME_LENGTH);
	check_null_octet((p + PROG_NAME_LENGTH));
	check_code_size((p + 4));
	(*player)->comment = (char *)malloc(sizeof(char) * (COMMENT_LENGTH + 1));
	err_allocate((*player)->comment);
	p += 4;
	(*player)->comment[COMMENT_LENGTH] = '\0';
	(*player)->comment = ft_strncpy((*player)->comment, (const char *)p, COMMENT_LENGTH);
	check_null_octet((p + COMMENT_LENGTH));
	hsize = lseek(fd, 0L, SEEK_END);
	hsize -= offset;
	
}