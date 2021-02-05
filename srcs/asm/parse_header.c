//
//  parse_header.c
//  corewar_asm
//
//  Created by Christian Deadshot on 2/5/21.
//  Copyright © 2021 Christian Deadshot. All rights reserved.
//

#include "asm.h"

int	read_str(char *dest, int len, t_asms *s)
{
	char	*str;
	int		i;
	int		k;
	
	k = 0;
	str = ft_strchr(s->str_str, '"');
	if (str == NULL)
		return (0);
	i = 1;
	while ((str[i] != '"') && (k <= len))
	{
		if (str[i] == '\0')
		{
			s = s->next;
			str = ft_strdup(s->str_str);
			i = 0;
		}
		dest[k] = str[i];
		i++;
		k++;
	}
	if (str[i] != '"')
	{
		ft_bzero(dest, len + 1);
		return (0);
	}
	return (1);
}

int	parse_name(t_asm **fc)
{
	char	*str;
	int		i;
	int		k;
	
	k = 0;
	str = ft_strchr((*fc)->s->str_str, '"');
	if (str == NULL)
		return (0);
	i = 1;
	while ((str[i] != '"') && (k <= PROG_NAME_LENGTH))
	{
		if (str[i] == '\0')
		{
			(*fc)->s = (*fc)->s->next;
			ft_strdup((*fc)->s->str_str);
			i = 0;
		}
		(*fc)->code->header.prog_name[k] = str[i];
		i++;
		k++;
	}
	if (str[i] != '"')
	{
		ft_bzero((*fc)->code->header.prog_name,
				 PROG_NAME_LENGTH + 1);
		return (0);
	}
	return (1);
}
