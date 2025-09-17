#include "dfa.h"
#include "init.h" 

void output()
{    
    // 写入输出文件
    // 1. 输出所有错误信息
    fprintf(output_file, "===== 错误信息 =====\n");
    printf( "===== 错误信息 =====\n");
    for (int i = 0; i < error_count; i++) {
        fprintf(output_file, "第%d行: %s\n",
            error_list[i].line, error_list[i].message);
        printf( "第%d行: %s\n",
            error_list[i].line, error_list[i].message);
    }

    // 2. 输出所有二元式
    fprintf(output_file, "\n===== 二元式列表 =====\n");
    printf( "\n===== 二元式列表 =====\n");
    for (int i = 0; i < tuple_count; i++) {
        fprintf(output_file, "<%-12s, %4d>  %s\n",
            tuple_list[i].type, tuple_list[i].code, tuple_list[i].lexeme);
        printf( "<%-12s, %4d>  %s\n",
            tuple_list[i].type, tuple_list[i].code, tuple_list[i].lexeme);
    }
    // 3. 输出符号表
    fprintf(output_file, "\n===== 标识符表 =====\n");
    printf( "\n===== 标识符表 =====\n");
    for (int i = 0; i < symbol_count; i++) {
        fprintf(output_file, "%-4d %s\n",
            symbol_table[i].id, symbol_table[i].name);
        printf( "%-4d %s\n",
            symbol_table[i].id, symbol_table[i].name);
    }
    // 4. 输出常数表
    fprintf(output_file, "\n===== 常数表 =====\n");
    printf("\n===== 常数表 =====\n");
    for (int i = 0; i < constant_count; i++) {
        if (constant_table[i].type == constant_table[i].INT_TYPE) {
            fprintf(output_file, "%-4d 整数 %d\n",
                constant_table[i].id, constant_table[i].int_val);
            printf("%-4d 整数 %d\n",
                constant_table[i].id, constant_table[i].int_val);
        }
        else {
            fprintf(output_file, "%-4d 浮点数 %.2f\n",
                constant_table[i].id, constant_table[i].float_val);
            printf( "%-4d 浮点数 %.2f\n",
                constant_table[i].id, constant_table[i].float_val);
        }
    }
    printf("分析完成！结果已保存至：%s\n", output_filename);
}