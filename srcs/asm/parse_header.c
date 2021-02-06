//
//  parse_header.c
//  corewar_asm
//
//  Created by Christian Deadshot on 2/5/21.
//  Copyright © 2021 Christian Deadshot. All rights reserved.
//

#include "asm.h"

t_asms	*read_str(char *dest, int len, t_asms *s)
{
	char	*str;
	int		i;
	int		k;
	
	k = 0;
	str = ft_strchr(s->str_str, '"');
	if (str == NULL)
		return (NULL);
	i = 1;
	while ((str[i] != '"') && (k <= len))
	{
		if (str[i] == '\0')
		{
			dest[k++] = '\n';
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
		return (NULL);
	}
	return (s);
}

