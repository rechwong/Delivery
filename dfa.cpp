#include "dfa.h"
#include "init.h"
//==================== �������� =====================
// ��Ӵ�����Ϣ�������б�
void add_error(int line, const char* message) {
    ErrorInfo* new_list = (ErrorInfo*)realloc(error_list, (error_count + 1) * sizeof(ErrorInfo));
    if (!new_list) {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    error_list = new_list;
    error_list[error_count].line = line;
    strncpy_s(error_list[error_count].message, 64, message, 63);
    error_count++;
}

// ��ӱ�ʶ�������ű��Զ�ȥ�أ�
int add_symbol(const char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return symbol_table[i].id;
        }
    }
    SymbolEntry* new_table = (SymbolEntry*)realloc(symbol_table, (symbol_count + 1) * sizeof(SymbolEntry));
    if (!new_table) exit(1);
    symbol_table = new_table;

    symbol_table[symbol_count].id = symbol_count + 1;
    strncpy_s(symbol_table[symbol_count].name, 32, name, 31);
    return ++symbol_count;
}

// ��ӳ������������Զ�ȥ�أ�
int add_constant(const char* lexeme, TokenType type) {
    if (type == TOKEN_INTEGER) {
        int value = atoi(lexeme);   //��C�����У�atoi���������ڽ��ַ���ת��Ϊ�����ı�׼�⺯����
        for (int i = 0; i < constant_count; i++) {
            if (constant_table[i].type == constant_table[i].INT_TYPE && constant_table[i].int_val == value) {
                return constant_table[i].id;
            }
        }
    }
    else {
        double value = atof(lexeme);
        for (int i = 0; i < constant_count; i++) {
            if (constant_table[i].type == constant_table[constant_count].FLOAT_TYPE &&
                constant_table[i].float_val == value) {
                return constant_table[i].id;
            }
        }
    }

    ConstantEntry* new_table = (ConstantEntry*)realloc(constant_table, (constant_count + 1) * sizeof(ConstantEntry));
    if (!new_table) exit(1);
    constant_table = new_table;

    constant_table[constant_count].id = constant_count + 1;
    if (type == TOKEN_INTEGER) {
        constant_table[constant_count].type = constant_table[constant_count].INT_TYPE;
        constant_table[constant_count].int_val = atoi(lexeme);
    }
    else {
        constant_table[constant_count].type = constant_table[constant_count].FLOAT_TYPE;
        constant_table[constant_count].float_val = atof(lexeme);
    }
    return ++constant_count;
}

// ��Ӷ�Ԫʽ���б�
void add_tuple(const char* type, int code, const char* lexeme) {
    Tuple* new_list = (Tuple*)realloc(tuple_list, (tuple_count + 1) * sizeof(Tuple));
    if (!new_list) exit(1);
    tuple_list = new_list;

    strncpy_s(tuple_list[tuple_count].type, 16, type, 15);
    tuple_list[tuple_count].code = code;
    strncpy_s(tuple_list[tuple_count].lexeme, 32, lexeme, 31);
    tuple_count++;
}
int is_keyword(const char* str) { //�жϹؼ���
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

//==================== ���ĺ��� =====================
Token get_next_token(const char* str, int* pos) {
    Token token = { TOKEN_ERROR, "", current_line };
    DfaState state = STATE_START; //��ʼ��״̬
    int lex_pos = 0;  //��������λ��
    unsigned char current;//��ǰ����ַ�

    while (1) {
        current = str[*pos];
        // �����кţ���״̬����ǰ��黻�У�
        if (current == '\n')
        {
            current_line++;
            size--;  //ftell�Ὣ�س�Ҳ��Ϊ�ַ������С
        }

        switch (state) {     
        case STATE_START:
            //isspace ������ C++ ��׼�������ڼ���ַ��Ƿ�Ϊ�հ��ַ��ĺ������� C++ �У��հ��ַ������ո�' '����ˮƽ�Ʊ����'\t'�������з���'\n'������ֱ�Ʊ����'\v'������ҳ����'\f'���ͻس�����'\r'��
            if (isspace((unsigned char)current)) {
                (*pos)++;
          //      if (current == '\n') current_line--; // �����кż���
                continue;
            }

            else if (isalpha(current) || current == '_') { // ��ʶ����ʼ
                token.lexeme[lex_pos++] = current;
                (*pos)++;
                state = STATE_ID;
            }
            else if (isdigit(current)) {          // ������ʼ     
                token.lexeme[lex_pos++] = current;
                (*pos)++;
                state = STATE_NUMBER;
            }
            else if (current == '/') {            // ������ע�ͻ����
                token.lexeme[lex_pos++] = current;
                (*pos)++;
                state = STATE_SLASH;
            }
            else if (current == '+' || current == '-' || current == '*' || current == '=') { // �����
                token.lexeme[lex_pos++] = current;
                token.lexeme[lex_pos] = '\0'; // �����ַ���
                token.type = TOKEN_OPERATOR;
                (*pos)++;
                return token;
            }
            else if (current == ';' || current == '(' || current == ')') { // �ָ���
                token.lexeme[lex_pos++] = current;
                token.lexeme[lex_pos] = '\0';
                token.type = TOKEN_DELIMITER;
                (*pos)++;
                return token;
            }
            else if (current == '\0') {           // �ַ�������
                return token;  // ���ش������ͣ��ɵ����ߴ������
            }
            else {                                // �Ƿ��ַ�����
                token.lexeme[lex_pos++] = current;
                token.lexeme[lex_pos] = '\0';
                snprintf(token.lexeme, 32, "�Ƿ��ַ� '%c'", current); // ��¼�Ƿ��ַ�
                (*pos)++;
                return token;
            }
            break;

        case STATE_ID:  // ʶ���ʶ��
            if (isalnum(current) || current == '_') { // ��Ч�ַ�
                if (lex_pos < 31) {  // ��ֹ���������
                    token.lexeme[lex_pos++] = current;
                    (*pos)++;
                }
                else {            // ��ʶ����������
                    strcpy_s(token.lexeme, 21, "��ʶ������");
                    return token;
                }
            }
            else {                // ��ʶ������  //����Ӧ�ж��Ƿ��Ǳ�����
                if (is_keyword(token.lexeme)  )//�Ǳ�����
                {
                token.type = TOKEN_KEYWORD;
                token.lexeme[lex_pos] = '\0';
                return token;
                }
                //else �Ǳ�ʶ��
                token.type = TOKEN_IDENTIFIER;
                token.lexeme[lex_pos] = '\0';
                return token;
            }
            break;

        case STATE_NUMBER:  // ʶ���������� 
            if (isdigit(current)) {
                token.lexeme[lex_pos++] = current;
                (*pos)++;
            }
            else if (current == '.') {    // ����С����
                token.lexeme[lex_pos++] = current;
                (*pos)++;
                state = STATE_FRACTION;
            }
            else {                        // ���ֽ���
                token.type = TOKEN_INTEGER;
                token.lexeme[lex_pos] = '\0';
                return token;
            }
            break;

        case STATE_FRACTION:  // ʶ��С������
            if (isdigit(current)) {
                token.lexeme[lex_pos++] = current;
                (*pos)++;
            }
            else {                        // С������
                // ���������һ��С�����֣���"123."�ǷǷ���������
                if (isdigit(token.lexeme[lex_pos - 1])) {
                    token.type = TOKEN_FLOAT;
                }
                else {
                    token.type = TOKEN_ERROR;
                    strcpy_s(token.lexeme, 21, "��Ч������");
                }
                token.lexeme[lex_pos] = '\0';
                return token;
            }
            break;
        case STATE_SLASH:  // ����б�ܺ��״̬�ж�
            if (current == '/') {         // ����ע��
                (*pos)++;
                state = STATE_SINGLE_COMMENT;
                lex_pos = 0; // ��մ��ػ�������������ע�����ݣ�
            }
            else if (current == '*') { // ����ע��           
                (*pos)++;
                state = STATE_MULTI_COMMENT;
                lex_pos = 0;  //��յ���
            }
            else {                     // ��ͨ���������
                token.type = TOKEN_OPERATOR;
                token.lexeme[lex_pos] = '\0';
                return token;
            }
            break;

        case STATE_SINGLE_COMMENT: // ������ע��
            if (current == '\n' || current == '\0') { // ע�ͽ���
                state = STATE_START; // �ص���ʼ״̬
                (*pos)++; // �������з�
            }
            else {
                (*pos)++; // ��������ע������
            }
            break;
        case STATE_MULTI_COMMENT:
            if(current == '*') {
                (*pos)++;
                if (str[*pos] == '/') { // ע�ͽ���
                    (*pos)++;
                    state = STATE_START;
                }
            }
            else if (current == '\0') { // �ļ�������ע��δ�պ�
               // add_error(current_line, "δ�պϵĶ���ע��");
                token.type = TOKEN_ERROR;
                strcpy_s(token.lexeme, 32, "ע��δ�պ�");
                return token;
            }
            else (*pos)++;
            break;
            
        }
    }
}

