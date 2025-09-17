#include "dfa.h"
#include "init.h"

//==================== ȫ�����ݽṹ ====================

SymbolEntry* symbol_table = NULL;    // ���ű�̬����
int symbol_count = 0;

ConstantEntry* constant_table = NULL;// ������̬����
int constant_count = 0;

ErrorInfo* error_list = NULL;        // ������Ϣ��̬����
int error_count = 0;

Tuple* tuple_list = NULL;            // ��Ԫʽ��̬����
int tuple_count = 0;

int current_line = 1; // ȫ�ֵ�ǰ�кż�����   ����  main�ⶨ��ȫ�ֱ��� 1. ͷ�ļ�extern int a 2. cpp int a = 1; 3. mainֱ����

char input_filename[256] = { 0 };   //Դ�ļ���ַ
char output_filename[256] = { 0 };  //����ļ���ַ

FILE* output_file = NULL;                      

 char* content = NULL;             //��ʱ������ַ

 long size = 0;

 const char* keywords[] = { "if", "else", "for", "while", "int", "return", "void","float","char"/* ... */};  //�ؼ��ֱ�
 int num_keywords = sizeof(keywords) / sizeof(keywords[0]);//�ؼ��ֱ�Ԫ������
// �����ļ���


int init() {

printf("������Դ�ļ�·����");
scanf_s("%255s", input_filename, (unsigned)_countof(input_filename));
printf("����������ļ�·����");
scanf_s("%255s", output_filename, (unsigned)_countof(output_filename));


// ��ȡ�ļ�����
FILE* input_file = NULL;
errno_t err_in = fopen_s(&input_file, input_filename, "r");
if (err_in != 0 || !input_file) {
    printf("�޷��������ļ�\n");
    return 1;
}

fseek(input_file, 0, SEEK_END);
size = ftell(input_file); //long size Ϊ�ظ�����   ftell�Ὣ���з���Ϊ�ַ����¶��.
fseek(input_file, 0, SEEK_SET);

content = (char*)malloc(size + 1);  //�洢Դ�ļ����ݵ���ʱ������ַ  //char*Ϊ�ظ�����

fread(content, 1, size, input_file);
content[size] = '\0';
fclose(input_file);

//������ļ�
errno_t err_out = fopen_s(&output_file, output_filename, "w");
if (err_out != 0 || !output_file) {
    printf("�޷���������ļ�\n");
    free(content);
    return 1;
                       }
}
