#pragma once
#ifndef DFA_H
#define DFA_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//--------------------- 词素类型定义 ------------------
typedef enum {
    TOKEN_IDENTIFIER,  // 标识符（变量名、函数名等）
    TOKEN_INTEGER,     // 整数
    TOKEN_FLOAT,       // 浮点数
    TOKEN_OPERATOR,    // 运算符（+、-、*、/、= 等）
    TOKEN_DELIMITER,   // 分隔符（;、()、{} 等）
    TOKEN_ERROR,        // 错误词素
    TOKEN_KEYWORD     //保留字
} TokenType;

//--------------------- 词素结构体 --------------------
typedef struct {
    TokenType type;    // 类型
    char lexeme[32];   // 词素内容（最大长度31）
    int line;          // 所在行号
} Token;

//--------------------- DFA状态定义 ------------------
typedef enum {
    STATE_START,            // 初始状态
    STATE_ID,               // 识别标识符
    STATE_NUMBER,           // 识别整数部分
    STATE_FRACTION,         // 识别小数部分
    STATE_SLASH,            // 遇到斜杠（可能是注释或除法）
    STATE_SINGLE_COMMENT,   // 单行注释
    STATE_MULTI_COMMENT,    // 多行注释
} DfaState;

// 符号表条目
typedef struct {
    int id;
    char name[32];
} SymbolEntry;
// 常数表条目（支持整数和浮点数）
typedef struct {
    int id;
    enum { INT_TYPE, FLOAT_TYPE } type;
    union {
        int int_val;
        double float_val;
    };
} ConstantEntry;

// 错误信息结构
typedef struct {
    int line;
    char message[64];
} ErrorInfo;

// 二元式结构
typedef struct {
    char type[16];
    int code;
    char lexeme[32];
} Tuple;

extern int current_line;



void scanner();

Token get_next_token(const char* str, int* pos);  //核心函数

void add_error(int line, const char* message);    //添加错误列表函数

// 添加标识符到符号表（自动去重）
int add_symbol(const char* name);

// 添加常数到常数表（自动去重）
int add_constant(const char* lexeme, TokenType type);

// 添加二元式到列表
void add_tuple(const char* type, int code, const char* lexeme);

int is_keyword(const char* str);

#endif // !DFA_H

