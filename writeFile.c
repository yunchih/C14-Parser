#include <stdio.h>
#include "writeFile.h"
#include "lineProcess.h"
#include "fileOperation.h"
#ifdef DEBUG
	#include "debug.h"
#endif

static void writePrimaryInstruction( FILE* out[] , Instruction* instruction );

static void writeSecondaryInstruction( FILE* out[] , Instruction* instruction , int freeSpacePos );

static void writeNextInstruction( FILE* out[] , int* position , List* list , int increment, int freeSpacePos );


/*
 * Don't forget that `writeCode` itself will increment file pointer , too 
 *
 */

void writeFile( FILE* out[] , Instruction* instruction , int instructions_number ){

	writePrimaryInstruction( out , instruction );
	resetFilePointer( out );
	writeSecondaryInstruction( out , instruction , instructions_number * 2 );
	writePosition( out[3] , instruction );

}
static void writePrimaryInstruction( FILE* out[] , Instruction* instruction ){

	#ifdef DEBUG
		log_info("Write primary");
	#endif
	while( instruction != NULL ){
		#ifdef DEBUG
			log_info("File position: %ld\n", ftell(out[0]));
		#endif
		writeCode( out , instruction->list->code );
		/* `writeCode` itself will increment file pointer, too */
		incrementPosition( out , 1 );
		instruction = instruction->next;
	}

}
static void writeSecondaryInstruction( FILE* out[] , Instruction* instruction , int freeSpacePos ){

	#ifdef DEBUG
		log_info("Write secondary");
	#endif
	incrementPosition( out , 1 );
	int position = 1;
	while( instruction != NULL ){
		writeNextInstruction( out , &position , instruction->list , 1, freeSpacePos );
		instruction = instruction->next;
	}
}
static void writeNextInstruction( 
		FILE* out[] ,
	   	int* position ,
	   	List* list ,
	   	int increment,
	   	int freeSpacePos ){

	#ifdef DEBUG
		log_info("File position: %ld\n", ftell(out[0]));
	#endif
	if( list->next == NULL ){
		list->next_position = END_POS;
		#ifdef DEBUG
			log_info("Save Pos: %d",list->next_position);
		#endif
		return;
	}

	writeCode( out , list->next->code );
	list->next_position = *position;

	#ifdef DEBUG
		log_info("Save Pos: %d",list->next_position);
	#endif
	incrementPosition( out , increment );
	(*position) += (increment+1);

	if( *position >= freeSpacePos )
		writeNextInstruction( out , position , list->next , 0 , freeSpacePos );
	else
		writeNextInstruction( out , position , list->next , 1 , freeSpacePos );
}
