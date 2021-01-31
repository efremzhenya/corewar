/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mellie <mellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:58:15 by lseema            #+#    #+#             */
/*   Updated: 2021/01/22 21:37:20 by mellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define COREWAR_USAGE			"USAGE: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ..."
# define ERR_1_MAX_PLAYERS		"ERROR: The number of players is more than allowed."
# define ERR_2_DUP_ID_PLAYER	"ERROR: ID_player must be unique."
# define ERR_3_READING_FAILED	"ERROR: Reading is failed."
# define ERR_4_CODE_MAXSIZE		"ERROR: The size of code is more than MaxSize."
# define ERR_5_INV_CODESIZE		"ERROR: The size of code != SIZE in the .cor file."
# define ASM_USAGE				"Usage: ./asm <sourcefile.s>."
# define ERROR_WRONG_EXTENSION	"Expected *.s file."
# define SYNTAX_ERROR			"Can't compile."
# define SYNTAX_ERROR_N			"Syntax error - unexpected end of input (Perhaps you forgot to end with a newline ?)"
#endif
