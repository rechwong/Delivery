#pragma once
#ifndef INIT_H
#define INIT_H

//==================== 全局数据结构 ====================

extern SymbolEntry* symbol_table ;    // 符号表动态数组
extern int symbol_count ;

extern ConstantEntry* constant_table ;// 常数表动态数组
extern int constant_count ;

extern ErrorInfo* error_list ;        // 错误信息动态数组
extern int error_count ;

extern Tuple* tuple_list ;            // 二元式动态数组
extern int tuple_count ;

extern char* content;//临时变量


extern char input_filename[256];
extern char output_filename[256];

extern FILE* output_file;

extern long size;//源文件大小

extern errno_t err_in;
extern errno_t err_out;

extern const char* keywords[]; //关键字表
extern int num_keywords;//关键字表元素数量

int init();
void output();
void close();

#endif // !


