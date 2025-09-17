#include "dfa.h"
#include "init.h"

//==================== 全局数据结构 ====================

SymbolEntry* symbol_table = NULL;    // 符号表动态数组
int symbol_count = 0;

ConstantEntry* constant_table = NULL;// 常数表动态数组
int constant_count = 0;

ErrorInfo* error_list = NULL;        // 错误信息动态数组
int error_count = 0;

Tuple* tuple_list = NULL;            // 二元式动态数组
int tuple_count = 0;

int current_line = 1; // 全局当前行号计数器   定义  main外定义全局变量 1. 头文件extern int a 2. cpp int a = 1; 3. main直接用

char input_filename[256] = { 0 };   //源文件地址
char output_filename[256] = { 0 };  //输出文件地址

FILE* output_file = NULL;                      

 char* content = NULL;             //临时变量地址

 long size = 0;

 const char* keywords[] = { "if", "else", "for", "while", "int", "return", "void","float","char"/* ... */};  //关键字表
 int num_keywords = sizeof(keywords) / sizeof(keywords[0]);//关键字表元素数量
// 输入文件名


int init() {

printf("请输入源文件路径：");
scanf_s("%255s", input_filename, (unsigned)_countof(input_filename));
printf("请输入输出文件路径：");
scanf_s("%255s", output_filename, (unsigned)_countof(output_filename));


// 读取文件内容
FILE* input_file = NULL;
errno_t err_in = fopen_s(&input_file, input_filename, "r");
if (err_in != 0 || !input_file) {
    printf("无法打开输入文件\n");
    return 1;
}

fseek(input_file, 0, SEEK_END);
size = ftell(input_file); //long size 为重复定义   ftell会将换行符视为字符导致多读.
fseek(input_file, 0, SEEK_SET);

content = (char*)malloc(size + 1);  //存储源文件内容的临时变量地址  //char*为重复定义

fread(content, 1, size, input_file);
content[size] = '\0';
fclose(input_file);

//打开输出文件
errno_t err_out = fopen_s(&output_file, output_filename, "w");
if (err_out != 0 || !output_file) {
    printf("无法创建输出文件\n");
    free(content);
    return 1;
                       }
}
