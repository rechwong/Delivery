#include "dfa.h"
#include "init.h"

void close() {

    // �ͷ���Դ
    free(content);
    free(symbol_table);
    free(constant_table);
    free(error_list);
    free(tuple_list);
    fclose(output_file);

}