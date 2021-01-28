//
//  utils.c
//  corewar
//
//  Created by Christian Deadshot on 1/27/21.
//  Copyright © 2021 Christian Deadshot. All rights reserved.
//

#include "asm.h"

int	ft_hex_to_dec(char *s)
{
	int	dec;

	dec = 0;

	return (dec);
}

char	*ft_dec_to_hex(int dec)
{
	char	*s;

	s = "";

	return (s);
}

void	int_to_bytecode(t_asm *fc, int value, int len)
{
	int		i;
	int		l;

	i = 0;
	l = len;
	while (len)
	{
		fc->code->code[fc->code->cpos + len - 1] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		len--;
	}
	fc->code->cpos += l;
}

char    *ft_itoa_base(int value, int base)
{
    char          *s;
    char          *sbase;
    int           digit;
    unsigned int  num;
    int           minus;

    sbase = "0123456789ABCDEF";
    digit = 1;
    minus = 1;
    if (value == 0)
      return("0\0");
    if (value < 0)
    {
      minus = -1;
      if (base == 10)
        digit++;
    }
    num = value * minus;
    while ((num /= base) > 0)
        digit++;
    s = (char *)malloc(sizeof(char) * digit + 1);
    s[digit] = '\0';
    if ((value < 0) && (base == 10))
      s[0] = '-';
    num = value * minus;
    while (num > 0)
    {
        digit--;
        s[digit] = sbase[num % base];
        num /= base;
    }
    return (s);
}
