#ifndef __LEX_ANALYSER_H__
#define __LEX_ANALYSER_H__

#include "./../tree_t/tree.h"

#define LEX_ANALYSER_MAX_VALUE_LENGTH 64
#define MAX_LEXEMS_COUNT 8192

enum key_t
{
	val     = 1,
	oper    = 2,
	kw      = 3,
	var     = 4,
	br      = 5,
	func    = 6,
	params  = 7
};

enum kw_t
{
	esli      = 1,
	inache    = 2,
	poka      = 3
};

struct lex_t
{
	enum key_t	key;
	char		value[ LEX_ANALYSER_MAX_VALUE_LENGTH ];
	double		koeff;
	struct func_t*	func;
};

struct analyser_t
{
	struct lex_t*    lexems[ MAX_LEXEMS_COUNT ];
	struct tree_t*   tree;
	char*            src;
	size_t           lex_num;
	size_t           src_sz;
	size_t           cur_pos;
};

struct func_t
{
	int		param_count;
	struct lex_t**	params_arr;
};

int	analyser_constr( struct analyser_t *analyser );
int	analyser_make_lexems( struct analyser_t *analyser );
int	getKW( struct lex_t *lexem, char *word, int word_sz );
int	getFUNC( struct lex_t *lexem, char *word, int word_sz );
int	getVAR( struct lex_t *lexem, char *word, int word_sz );
char*	getVAL( char *src, struct lex_t *lexem );
char*	getOPER( char *src, struct lex_t *lexem );
char*	getBR( char *src, struct lex_t *lexem );

#define check_for_lexem( ARG, key_num )							\
if( is##ARG )										\
{											\
	struct lex_t *lexem = ( struct lex_t * )calloc( 1, sizeof( struct lex_t ) );	\
	check_pointer( lexem, 1 );							\
											\
	lexem -> key = key_num;								\
											\
	src = get##ARG ( src, lexem );							\
	check_pointer( src, 1 );							\
											\
	analyser -> lexems[ analyser -> lex_num ++ ] = lexem;				\
											\
	continue;									\
}

#define check_for_word( ARG, key_num )							\
if( is##ARG )										\
{											\
	struct lex_t *lexem = ( struct lex_t * )calloc( 1, sizeof( struct lex_t ) );	\
	check_pointer( lexem, 1 );							\
											\
	lexem -> key = key_num;								\
											\
	get##ARG ( lexem, word, word_sz );						\
											\
	analyser -> lexems[ analyser -> lex_num ++ ] = lexem;				\
											\
	continue;									\
}

#define isTRASH \
elem == ' ' || elem == '\n' || elem == '\t' || elem == '\v' || elem == ',' || elem == ';'


#define isVAL \
'0' <= elem && elem <= '9'


#define isOPER \
elem == '+' || elem == '-' || elem == '/' || elem == '*' || elem == '='


#define isBR \
elem == '(' || elem == ')' || elem == '[' || elem == ']' || elem == '<' || elem == '>'


#define isLETTER ( 'a' <= elem && 'z' >= elem ) || ( 'A' <= elem && 'Z' >= elem )


#define isKW \
!( strcmp( word, "esli" ) * strcmp( word, "inache" ) * strcmp( word, "poka" ) )


#define isFUNC \
*src == '<'


#define isVAR \
1 == 1 			// just to kill if()

#endif /*__LEX_ANALYSER_H__*/