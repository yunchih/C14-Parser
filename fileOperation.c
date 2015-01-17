#include <stdio.h>
#include "fileOperation.h"
#include "lineProcess.h"
#include "writeFile.h"
#ifdef DEBUG
	#include "debug.h"
#endif
void incrementPosition( FILE* out[] , int increment ){
	for (int i = 0; i < CODE_FILE_NUM ; ++i)
		fseek( out[i] , increment , SEEK_CUR );
}
void resetFilePointer( FILE* out[] ){
	for (int i = 0; i < FILENUM; ++i)
		rewind( out[i] );
}
void writeCode( FILE* out[] , Code code ){
	for (int i = 0; i < CODE_FILE_NUM; ++i){
		#ifdef DEBUG
			printf("Write into file %d at %ld\n",i,ftell(out[i]) );
			dump_code( code , 8 );
		#endif
		fwrite(&code,sizeof(char),1,out[i]);	
		code >>= FieldSize;	
	}
}
void writePosition( FILE* file , Instruction* instruction ){
	#ifdef DEBUG
		log_info("Write Memory.bin:");
	#endif
	while( instruction != NULL ){
		List* list = instruction->list;
		while( list != NULL ){
			#ifdef DEBUG
				printf("Write into file at %ld\n",ftell(file) );
				dump_code( list->next_position , 8 );
			#endif
			fwrite(&(list->next_position),sizeof(char),1,file);
			list = list->next;
		}
		instruction = instruction->next;
	}
}
