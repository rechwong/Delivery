#pragma once
#ifndef INIT_H
#define INIT_H

//==================== ȫ�����ݽṹ ====================

extern SymbolEntry* symbol_table ;    // ���ű�̬����
extern int symbol_count ;

extern ConstantEntry* constant_table ;// ������̬����
extern int constant_count ;

extern ErrorInfo* error_list ;        // ������Ϣ��̬����
extern int error_count ;

extern Tuple* tuple_list ;            // ��Ԫʽ��̬����
extern int tuple_count ;

extern char* content;//��ʱ����


extern char input_filename[256];
extern char output_filename[256];

extern FILE* output_file;

extern long size;//Դ�ļ���С

extern errno_t err_in;
extern errno_t err_out;

extern const char* keywords[]; //�ؼ��ֱ�
extern int num_keywords;//�ؼ��ֱ�Ԫ������

int init();
void output();
void close();

#endif // !


