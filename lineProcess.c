#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lineProcess.h"
#include "table.h"
#ifdef DEBUG
	#include "debug.h"
#endif

static Code setCode( char* buffer , Code* code );

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

		printf("Buffer: %s",buffer);
		comment_position = strchr( buffer, ';' );
		if( comment_position != NULL ) /* Ignore anything after ; */
			*comment_position = '\0' ;

		colon_position   = strchr( buffer, ':' );

		int isEmptyLine;
		if( colon_position != NULL )
			isEmptyLine = setCode( colon_position , &code );
		else
			isEmptyLine = setCode( buffer , &code );
		
		if( isEmptyLine == 1 ) /* Ignore empty line */
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
			next_instruction->position = 0;
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

static Code setCode( char* buffer , Code* code ){

	char delim[] = " ,:\t\n";
	char* token = strtok( buffer , delim );

	int isEmptyLine = 1;
	*code = 0;
	while( token != NULL ){
		#ifdef DEBUG
			log_info("Get token: %s",token);
		#endif
		(*code) |= fetchCode( token );	
		token = strtok( NULL , delim );
		isEmptyLine = 0;
	}
	return isEmptyLine;
}
#ifdef DEBUG

	
#endif
