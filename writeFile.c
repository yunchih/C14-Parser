#include <stdio.h>
#include "writeFile.h"
#include "lineProcess.h"
#include "fileOperation.h"
#ifdef DEBUG
	#include "debug.h"
#endif

static void writePrimaryInstruction( FILE* out[] , Instruction* instruction );

static void writeSecondaryInstruction( FILE* out[] , Instruction* instruction , int freeSpacePos );

static void writeNextInstruction( FILE* out[] , List* list , int freeSpacePos );


/*
 * Don't forget that `writeCode` itself will increment file pointer , too 
 *
 */

void writeFile( FILE* out[] , Instruction* instruction , int instructions_number ){

	writePrimaryInstruction( out , instruction );
	resetFilePointer( out );
	writeSecondaryInstruction( out , instruction , ( instructions_number-1 ) * 2 );
	writePosition( out[3] , instruction );

}
static void writePrimaryInstruction( FILE* out[] , Instruction* instruction ){

	#ifdef DEBUG
		log_info("Write primary");
	#endif
	while( instruction != NULL ){
		#ifdef DEBUG
			log_info("File position: %ld", ftell(out[0]));
		#endif
		instruction->position = ftell( out[0] );
		writeCode( out , instruction->list->code );
		/* `writeCode` itself will increment file pointer, too */
		incrementPosition( out );
		instruction = instruction->next;
	}

}
static void writeSecondaryInstruction( FILE* out[] , Instruction* instruction , int freeSpacePos ){

	#ifdef DEBUG
		log_info("Write secondary");
	#endif
	incrementPosition( out );
	while( instruction != NULL ){
		#ifdef DEBUG
			puts("------------------------");
			log_info("Instruction name: %s",instruction->name);
		#endif
		writeNextInstruction( out , instruction->list , freeSpacePos );
		instruction = instruction->next;
	}
}
static void writeNextInstruction( FILE* out[] , List* list , int freeSpacePos ){

	#ifdef DEBUG
		log_info("File position: %ld\n", ftell(out[0]));
	#endif
	if( list->next == NULL ){
		list->next_position = END_POS;
		#ifdef DEBUG
			log_info("No further instruction");
		#endif
		return;
	}

	list->next_position = ftell(out[0]);
	writeCode( out , list->next->code );

	if( list->next_position < freeSpacePos )
		incrementPosition( out );

	#ifdef DEBUG
		log_info("Next instruction at %ld",list->next_position);
	#endif
	writeNextInstruction( out , list->next , freeSpacePos );
}
