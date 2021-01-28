/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 21:29:47 by mellie            #+#    #+#             */
/*   Updated: 2021/01/22 21:38:07 by mellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	ft_read_sfile(t_asm *fc)
{
	ssize_t	rlen;
	int		str_count;
	
	str_count = 0;
	fc->s = (t_asms *)malloc(sizeof(t_asms));
	err_allocate(fc->s);
	fc->s->next = NULL;
	fc->s->str_num = str_count;
	fc->first_s = fc->s;
	rlen = get_next_line(fc->fd, &fc->s->str_str);
	while (rlen > 0)
	{
		fc->s->next = (t_asms *)malloc(sizeof(t_asms));
		err_allocate(fc->s->next);
		fc->s = fc->s->next;
		fc->s->str_num = ++str_count;
		fc->s->next = NULL;
		rlen = get_next_line(fc->fd, &fc->s->str_str);
	}
	return (1);
}

int	ft_write_corfile(t_asm *fc)
{
	char	*str_err;
	
	fc->fw = open(fc->ex_file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fc->fw == -1)
	{
		str_err = ft_strjoin("ERROR: Can't create file: ", fc->ex_file);
		terminate(str_err);
	}
	if (ft_strstr(fc->first_s->str_str, NAME_CMD_STRING))
	{
		str_err = ft_strsub(fc->first_s->str_str, 7, 8);
	}
	ft_putstr_fd(str_err, fc->fw);
	
	ft_putstr_fd(fc->code->code, fc->fw);
	write(fc->fw, fc->code->code, fc->code->cpos);
	close(fc->fw);
	return (1);
}

int	init_fc(t_asm *fc, const char *av)
{
	char	*s0;
	char	*s1;
	char	*str_err;
	
	
	fc->fd = open (av, O_RDONLY);
	if (fc->fd == -1)
	{
		str_err = ft_strjoin("ERROR: Can't open file: ", av);
		terminate(str_err);
	}

	s1 = ft_strrchr(av, '.');
	s0 = ft_strsub(av, 0, ft_strlen(av) - ft_strlen(s1));
	if (ft_strcmp(s1, ".s") != 0)
		terminate(ERROR_WRONG_EXTENSION);
	
	fc->ex_file = ft_strjoin(s0, ".cor");
	
	return (1);
}

int main(int argc, const char * argv[]) {
	
	t_asm	*fc;
	char	*str_err;
	
	if (argc < 2)
		terminate(ASM_USAGE);

	fc = (t_asm *)malloc(sizeof(t_asm));
	err_allocate(fc);

	if (!init_fc(fc, argv[argc - 1]))
		terminate(ERR_3_READING_FAILED);
	
	if (!ft_read_sfile(fc))
	{
		str_err = ft_strjoin("ERROR: Can't read file: ", argv[argc - 1]);
		terminate(str_err);
	}
	
	if (asmparse(fc) != 0)
		terminate(SYNTAX_ERROR);
	
	if (!ft_write_corfile(fc))
		terminate(ERR_3_READING_FAILED);
    return (0);
}
