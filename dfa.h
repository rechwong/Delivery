#pragma once
#ifndef DFA_H
#define DFA_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//--------------------- �������Ͷ��� ------------------
typedef enum {
    TOKEN_IDENTIFIER,  // ��ʶ�������������������ȣ�
    TOKEN_INTEGER,     // ����
    TOKEN_FLOAT,       // ������
    TOKEN_OPERATOR,    // �������+��-��*��/��= �ȣ�
    TOKEN_DELIMITER,   // �ָ�����;��()��{} �ȣ�
    TOKEN_ERROR,        // �������
    TOKEN_KEYWORD     //������
} TokenType;

//--------------------- ���ؽṹ�� --------------------
typedef struct {
    TokenType type;    // ����
    char lexeme[32];   // �������ݣ���󳤶�31��
    int line;          // �����к�
} Token;

//--------------------- DFA״̬���� ------------------
typedef enum {
    STATE_START,            // ��ʼ״̬
    STATE_ID,               // ʶ���ʶ��
    STATE_NUMBER,           // ʶ����������
    STATE_FRACTION,         // ʶ��С������
    STATE_SLASH,            // ����б�ܣ�������ע�ͻ������
    STATE_SINGLE_COMMENT,   // ����ע��
    STATE_MULTI_COMMENT,    // ����ע��
} DfaState;

// ���ű���Ŀ
typedef struct {
    int id;
    char name[32];
} SymbolEntry;
// ��������Ŀ��֧�������͸�������
typedef struct {
    int id;
    enum { INT_TYPE, FLOAT_TYPE } type;
    union {
        int int_val;
        double float_val;
    };
} ConstantEntry;

// ������Ϣ�ṹ
typedef struct {
    int line;
    char message[64];
} ErrorInfo;

// ��Ԫʽ�ṹ
typedef struct {
    char type[16];
    int code;
    char lexeme[32];
} Tuple;

extern int current_line;



void scanner();

Token get_next_token(const char* str, int* pos);  //���ĺ���

void add_error(int line, const char* message);    //��Ӵ����б���

// ��ӱ�ʶ�������ű��Զ�ȥ�أ�
int add_symbol(const char* name);

// ��ӳ������������Զ�ȥ�أ�
int add_constant(const char* lexeme, TokenType type);

// ��Ӷ�Ԫʽ���б�
void add_tuple(const char* type, int code, const char* lexeme);

int is_keyword(const char* str);

#endif // !DFA_H

