
#ifndef LINEPROCESS_H_LYQBK8NU
#define LINEPROCESS_H_LYQBK8NU

#include "table.h"


typedef struct List{
	Code code;
	int next_position;
	struct List *next;
} List;
typedef struct Instruction{
	List* list;
	char *name;
	struct Instruction *next;
} Instruction;

#define BufferSize 400

void getInstructions( FILE* src , Instruction** instructions , int* instructions_number );


#endif /* end of include guard: LINEPROCESS_H_LYQBK8NU */

