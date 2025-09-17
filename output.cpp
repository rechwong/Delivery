#include "dfa.h"
#include "init.h" 

void output()
{    
    // д������ļ�
    // 1. ������д�����Ϣ
    fprintf(output_file, "===== ������Ϣ =====\n");
    printf( "===== ������Ϣ =====\n");
    for (int i = 0; i < error_count; i++) {
        fprintf(output_file, "��%d��: %s\n",
            error_list[i].line, error_list[i].message);
        printf( "��%d��: %s\n",
            error_list[i].line, error_list[i].message);
    }

    // 2. ������ж�Ԫʽ
    fprintf(output_file, "\n===== ��Ԫʽ�б� =====\n");
    printf( "\n===== ��Ԫʽ�б� =====\n");
    for (int i = 0; i < tuple_count; i++) {
        fprintf(output_file, "<%-12s, %4d>  %s\n",
            tuple_list[i].type, tuple_list[i].code, tuple_list[i].lexeme);
        printf( "<%-12s, %4d>  %s\n",
            tuple_list[i].type, tuple_list[i].code, tuple_list[i].lexeme);
    }
    // 3. ������ű�
    fprintf(output_file, "\n===== ��ʶ���� =====\n");
    printf( "\n===== ��ʶ���� =====\n");
    for (int i = 0; i < symbol_count; i++) {
        fprintf(output_file, "%-4d %s\n",
            symbol_table[i].id, symbol_table[i].name);
        printf( "%-4d %s\n",
            symbol_table[i].id, symbol_table[i].name);
    }
    // 4. ���������
    fprintf(output_file, "\n===== ������ =====\n");
    printf("\n===== ������ =====\n");
    for (int i = 0; i < constant_count; i++) {
        if (constant_table[i].type == constant_table[i].INT_TYPE) {
            fprintf(output_file, "%-4d ���� %d\n",
                constant_table[i].id, constant_table[i].int_val);
            printf("%-4d ���� %d\n",
                constant_table[i].id, constant_table[i].int_val);
        }
        else {
            fprintf(output_file, "%-4d ������ %.2f\n",
                constant_table[i].id, constant_table[i].float_val);
            printf( "%-4d ������ %.2f\n",
                constant_table[i].id, constant_table[i].float_val);
        }
    }
    printf("������ɣ�����ѱ�������%s\n", output_filename);
}