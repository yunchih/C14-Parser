#ifndef FILEOPERATION_H_9XFPLZZG
#define FILEOPERATION_H_9XFPLZZG

#include "lineProcess.h"
#include "table.h"

#define FieldSize 8
#define FieldMask 0x11111111
#define END_POS 0xFF

void incrementPosition( FILE* out[] , int increment );

void resetFilePointer( FILE* out[] );

void writeCode( FILE* out[] , Code code );

void writePosition( FILE* file , Instruction* instruction );

#endif /* end of include guard: FILEOPERATION_H_9XFPLZZG */
