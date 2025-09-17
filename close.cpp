#include "dfa.h"
#include "init.h"

void close() {

    // สอทลืสิด
    free(content);
    free(symbol_table);
    free(constant_table);
    free(error_list);
    free(tuple_list);
    fclose(output_file);

}