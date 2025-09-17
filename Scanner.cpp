#include "dfa.h"
#include "init.h"

//=================== 主函数 =========================
void scanner()
{
    // 词法分析处理
    int pos = 0;
    while (pos < size) {
        Token token = get_next_token(content, &pos);

        // 错误处理
        if (token.type == TOKEN_ERROR) {
            add_error(token.line, token.lexeme);
            continue;
        }
        // 生成二元式
        const char* type_str = "";
        int code = 0;

        switch (token.type) {
        case TOKEN_IDENTIFIER:
            type_str = "IDENTIFIER";                         //标识符
            code = add_symbol(token.lexeme);
            break;
        case TOKEN_INTEGER:
            type_str = "INTEGER";                            //整数
            code = add_constant(token.lexeme, TOKEN_INTEGER);
            break;
        case TOKEN_FLOAT:
            type_str = "FLOAT";                              //浮点数
            code = add_constant(token.lexeme, TOKEN_FLOAT);
            break;
        case TOKEN_OPERATOR:
            type_str = "OPERATOR";                            //运算符
            code = 0; // 运算符单独编码可扩展
            break;
        case TOKEN_DELIMITER:                                 //界符(分隔符)
            type_str = "DELIMITER";
            code = 0;
            break;
        case TOKEN_KEYWORD:                                   //保留字

            type_str = token.lexeme;
            code = 0;
            break;
        }

        add_tuple(type_str, code, token.lexeme);
    }
    output();//输出文件
}
