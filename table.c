#include <string.h>
#include "table.h"
#ifdef DEBUG
	#include "debug.h"
#endif

CodeTable codeTable[] = {
	{ "A", 0b100000000010010000010001 },
	{ "B", 0b010000000010010000010001 },
	{ "C", 0b001000000010010000010001 },
	{ "D", 0b000100000010010000010001 },
	{ "E", 0b000010000010010000010001 },
	{ "One", 0b000000000000000000000001},
};

int CodeTableSize = sizeof( codeTable ) / sizeof( CodeTable );

Code fetchCode( char* name ){
	for (int i = 0; i < CodeTableSize; ++i)
		if( strcmp( name , codeTable[i].name ) == 0 )
			return codeTable[i].code;
	return 0;
}
