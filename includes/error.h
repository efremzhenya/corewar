/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:58:15 by lseema            #+#    #+#             */
/*   Updated: 2021/01/31 18:12:57 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define COREWAR_USAGE2			"USAGE: ./corewar [[-dump nbr_cycles] | [-v]] ["
# define COREWAR_USAGE			COREWAR_USAGE2 "[-n number] champion1.cor] ...]"
# define ER						"ERROR: "
# define ERR_1_MAX_PLAYERS		ER "The number of players is more than allowed."
# define ERR_2_DUP_ID_PLAYER	ER "ID_player must be unique."
# define ERR_3_READING_FAILED	ER "Reading is failed."
# define ERR_4_CODE_MAXSIZE		ER "The size of code is more than MaxSize."
# define ERR_5_INV_CODESIZE		ER "The size of code != SIZE in the .cor file."
# define ERR_VISUAL_ON_ALLOC	ER "Not allocated memory for visual mode."
# define ASM_USAGE				"Usage: ./asm <sourcefile.s>."
# define ERROR_WRONG_EXTENSION	"Expected *.s file."
# define SYNTAX_ERROR			"Can't compile."
#endif
