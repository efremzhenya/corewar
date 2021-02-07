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

t_asms	*new_s(void)
{
	t_asms	*s;
	s = (t_asms *)malloc(sizeof(t_asms));
	err_allocate(s);
	s->next = NULL;
	return (s);
}

int	ft_read_sfile(t_asm *fc)
{
	ssize_t	rlen;
	int		str_count;
	char	*line;
	
	str_count = 0;
	rlen = get_next_line(fc->fd, &line);
	if (rlen > 0)
	{
		fc->s = new_s();
		fc->s->str_num = ++str_count;
		fc->s->str_str = ft_strdup(line);
	}
	else
		terminate(ERR_3_READING_FAILED);
	
	fc->first_s = fc->s;
	while (rlen > 0)
	{
		rlen = get_next_line(fc->fd, &line);
		if (rlen > 0)
		{
			fc->s->next = new_s();
			fc->s = fc->s->next;
			fc->s->str_num = ++str_count;
			fc->s->str_str = ft_strdup(line);
		}
	}
//	if (fc->s->str_str[ft_strlen(fc->s->str_str) - 1] != '\n')
//		terminate(SYNTAX_ERROR_N);
	
//	lseek(fc->fd, 0, 2);
//	read(fc->fd, line, 1);
	
	free(line);
	close(fc->fd);
	return (1);
}

int	ft_write_corfile(t_asm *fc)
{
	char	*str_err;
	
	//fc->fw = open(fc->ex_file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	fc->fw = open(fc->ex_file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fc->fw == -1)
	{
		str_err = ft_strjoin("ERROR: Can't create file: ", fc->ex_file);
		terminate(str_err);
	}
	
	if (ft_strstr(fc->first_s->str_str, NAME_CMD_STRING))
	{
		str_err = ft_strsub(fc->first_s->str_str, 7, 8);
	}
	
	write(fc->fw, fc->code->code, fc->code->cpos);
	
	ft_putstr_fd(str_err, fc->fw);
	str_err = int_to_bytecode_ch(-14, 2);
	write(fc->fw, "\0\0\0\0", 4);
	write(fc->fw, str_err, ft_strlen(str_err));
	
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
	
	fc->fw = 0;
	fc->ex_file = ft_strjoin(s0, ".cor");
	fc->s = NULL;
	fc->first_s = NULL;
	fc->s_err = NULL;
	fc->first_err = NULL;
	fc->warnings = 0;
	fc->critical = 0;
	fc->ignored = 0;
	fc->cor = NULL;
	fc->first_cor = NULL;
	fc->label = NULL;
	
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
