#ifndef TABLE_H_Q9EBQVPF
#define TABLE_H_Q9EBQVPF


typedef unsigned int Code;


typedef struct {
	char* name;
	Code code;
} CodeTable;

Code fetchCode( char* name );

#endif /* end of include guard: TABLE_H_Q9EBQVPF */
