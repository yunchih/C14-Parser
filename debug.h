#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define Test(NAME, args... ) void Test_##NAME( args )

#define TEST(FUNC, args...) do{ printf( ANSI_COLOR_GREEN "---" #FUNC "---\n" ANSI_COLOR_RESET ); Test_##FUNC( args ); }while(0)

#ifdef DEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, ANSI_COLOR_RED "[ERROR] (%s:%d: errno: %s) " M "\n" ANSI_COLOR_RESET, __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, ANSI_COLOR_YELLOW "[INFO] (%s:%d) " M "\n" ANSI_COLOR_RESET, __FILE__, __LINE__, ##__VA_ARGS__)


void dump_file( char* fileName[] );
void dump_code( Code code , int BitsNum );

#endif
