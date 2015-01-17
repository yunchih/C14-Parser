#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lineProcess.h"
#include "table.h"
#ifdef DEBUG
	#include "debug.h"
#endif

static Code getCode( char* buffer );

void getInstructions( FILE* src , Instruction** instructions , int* instructions_number ){

	Code code;
	char *comment_position;
	char *colon_position;
	char buffer[ BufferSize ];	

	Instruction *cur_instruction;
	Instruction *next_instruction;
	List *cur_list;
	List *next_list;

	while( fgets( buffer , BufferSize , src ) != NULL ){

		comment_position = strchr( buffer, ';' );
		if( comment_position != NULL ) /* Ignore anything after ; */
			*comment_position = '\0' ;

		colon_position   = strchr( buffer, ':' );

		if( colon_position   != NULL )
			code = getCode( colon_position );
		else
			code = getCode( buffer );
		
		if( code == 0 ) /* Ignore empty line */
			continue;

		next_list = malloc( sizeof(List) );
		next_list->next = NULL;
		next_list->code = code; 
		#ifdef DEBUG
			dump_code( code , 24 );
		#endif

		/*
		 * If it is the first cyle of a multiple cycle instruction
		 * Then push that instruction into our list
		 */
		if( colon_position != NULL ){  

			char* instruction_name = strtok( buffer , ": " );
			next_instruction = malloc( sizeof(Instruction) );
			next_instruction->list = next_list;
			next_instruction->next = NULL;
			next_instruction->name = malloc( strlen(instruction_name)+1 );
			strcpy( next_instruction->name , instruction_name );
			#ifdef DEBUG
				log_info("Get Instruction: %s",next_instruction->name);
			#endif

			if( *instructions == NULL )
				*instructions = next_instruction;
			else
				cur_instruction->next = next_instruction;
			
			cur_instruction = next_instruction;
			(*instructions_number)++;
		}
		else{
			cur_list->next = next_list;
		}

		cur_list = next_list;
		
		#ifdef DEBUG
			puts("-------------------------");
		#endif
	}
}
static Code getCode( char* buffer ){

	char delim[] = " ,:\t";
	char* token = strtok( buffer , delim );

	Code code = 0;
	while( token != NULL ){
		#ifdef DEBUG
			log_info("Get token: %s",token);
		#endif
		code |= fetchCode( token );	
		token = strtok( NULL , delim );
	}
	return code;
}
#ifdef DEBUG

	
#endif
