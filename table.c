#include <string.h>
#include "table.h"
#ifdef DEBUG
	#include "debug.h"
#endif

CodeTable codeTable[] = {
	{ "One", 0b000000000000000000000001},
	{ "Two", 0b000000000000000000000010},
	{ "Three", 0b000000000000000000000011},
	{ "256",0b000000000000000100000000},
	{ "more",0b000000010000000000000000},
	{ "many",0b111111111111111111111111}

};

int CodeTableSize = sizeof( codeTable ) / sizeof( CodeTable );

Code fetchCode( char* name ){
	for (int i = 0; i < CodeTableSize; ++i)
		if( strcmp( name , codeTable[i].name ) == 0 )
			return codeTable[i].code;
	return 0;
}
