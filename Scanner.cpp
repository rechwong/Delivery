#include "dfa.h"
#include "init.h"

//=================== ������ =========================
void scanner()
{
    // �ʷ���������
    int pos = 0;
    while (pos < size) {
        Token token = get_next_token(content, &pos);

        // ������
        if (token.type == TOKEN_ERROR) {
            add_error(token.line, token.lexeme);
            continue;
        }
        // ���ɶ�Ԫʽ
        const char* type_str = "";
        int code = 0;

        switch (token.type) {
        case TOKEN_IDENTIFIER:
            type_str = "IDENTIFIER";                         //��ʶ��
            code = add_symbol(token.lexeme);
            break;
        case TOKEN_INTEGER:
            type_str = "INTEGER";                            //����
            code = add_constant(token.lexeme, TOKEN_INTEGER);
            break;
        case TOKEN_FLOAT:
            type_str = "FLOAT";                              //������
            code = add_constant(token.lexeme, TOKEN_FLOAT);
            break;
        case TOKEN_OPERATOR:
            type_str = "OPERATOR";                            //�����
            code = 0; // ����������������չ
            break;
        case TOKEN_DELIMITER:                                 //���(�ָ���)
            type_str = "DELIMITER";
            code = 0;
            break;
        case TOKEN_KEYWORD:                                   //������

            type_str = token.lexeme;
            code = 0;
            break;
        }

        add_tuple(type_str, code, token.lexeme);
    }
    output();//����ļ�
}
