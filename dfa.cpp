#include "dfa.h"
#include "init.h"
//==================== 辅助函数 =====================
// 添加错误信息到错误列表
void add_error(int line, const char* message) {
    ErrorInfo* new_list = (ErrorInfo*)realloc(error_list, (error_count + 1) * sizeof(ErrorInfo));
    if (!new_list) {
        printf("内存分配失败！\n");
        exit(1);
    }
    error_list = new_list;
    error_list[error_count].line = line;
    strncpy_s(error_list[error_count].message, 64, message, 63);
    error_count++;
}

// 添加标识符到符号表（自动去重）
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

// 添加常数到常数表（自动去重）
int add_constant(const char* lexeme, TokenType type) {
    if (type == TOKEN_INTEGER) {
        int value = atoi(lexeme);   //在C语言中，atoi函数是用于将字符串转换为整数的标准库函数。
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

// 添加二元式到列表
void add_tuple(const char* type, int code, const char* lexeme) {
    Tuple* new_list = (Tuple*)realloc(tuple_list, (tuple_count + 1) * sizeof(Tuple));
    if (!new_list) exit(1);
    tuple_list = new_list;

    strncpy_s(tuple_list[tuple_count].type, 16, type, 15);
    tuple_list[tuple_count].code = code;
    strncpy_s(tuple_list[tuple_count].lexeme, 32, lexeme, 31);
    tuple_count++;
}
int is_keyword(const char* str) { //判断关键字
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

//==================== 核心函数 =====================
Token get_next_token(const char* str, int* pos) {
    Token token = { TOKEN_ERROR, "", current_line };
    DfaState state = STATE_START; //初始化状态
    int lex_pos = 0;  //单个单词位置
    unsigned char current;//当前检查字符

    while (1) {
        current = str[*pos];
        // 处理行号（在状态处理前检查换行）
        if (current == '\n')
        {
            current_line++;
            size--;  //ftell会将回车也认为字符计算大小
        }

        switch (state) {     
        case STATE_START:
            //isspace 函数是 C++ 标准库中用于检查字符是否为空白字符的函数。在 C++ 中，空白字符包括空格（' '）、水平制表符（'\t'）、换行符（'\n'）、垂直制表符（'\v'）、换页符（'\f'）和回车符（'\r'）
            if (isspace((unsigned char)current)) {
                (*pos)++;
          //      if (current == '\n') current_line--; // 修正行号计数
                continue;
            }

            else if (isalpha(current) || current == '_') { // 标识符起始
                token.lexeme[lex_pos++] = current;
                (*pos)++;
                state = STATE_ID;
            }
            else if (isdigit(current)) {          // 数字起始     
                token.lexeme[lex_pos++] = current;
                (*pos)++;
                state = STATE_NUMBER;
            }
            else if (current == '/') {            // 可能是注释或除法
                token.lexeme[lex_pos++] = current;
                (*pos)++;
                state = STATE_SLASH;
            }
            else if (current == '+' || current == '-' || current == '*' || current == '=') { // 运算符
                token.lexeme[lex_pos++] = current;
                token.lexeme[lex_pos] = '\0'; // 结束字符串
                token.type = TOKEN_OPERATOR;
                (*pos)++;
                return token;
            }
            else if (current == ';' || current == '(' || current == ')') { // 分隔符
                token.lexeme[lex_pos++] = current;
                token.lexeme[lex_pos] = '\0';
                token.type = TOKEN_DELIMITER;
                (*pos)++;
                return token;
            }
            else if (current == '\0') {           // 字符串结束
                return token;  // 返回错误类型，由调用者处理结束
            }
            else {                                // 非法字符处理
                token.lexeme[lex_pos++] = current;
                token.lexeme[lex_pos] = '\0';
                snprintf(token.lexeme, 32, "非法字符 '%c'", current); // 记录非法字符
                (*pos)++;
                return token;
            }
            break;

        case STATE_ID:  // 识别标识符
            if (isalnum(current) || current == '_') { // 有效字符
                if (lex_pos < 31) {  // 防止缓冲区溢出
                    token.lexeme[lex_pos++] = current;
                    (*pos)++;
                }
                else {            // 标识符过长错误
                    strcpy_s(token.lexeme, 21, "标识符过长");
                    return token;
                }
            }
            else {                // 标识符结束  //这里应判断是否是保留字
                if (is_keyword(token.lexeme)  )//是保留字
                {
                token.type = TOKEN_KEYWORD;
                token.lexeme[lex_pos] = '\0';
                return token;
                }
                //else 是标识符
                token.type = TOKEN_IDENTIFIER;
                token.lexeme[lex_pos] = '\0';
                return token;
            }
            break;

        case STATE_NUMBER:  // 识别整数部分 
            if (isdigit(current)) {
                token.lexeme[lex_pos++] = current;
                (*pos)++;
            }
            else if (current == '.') {    // 遇到小数点
                token.lexeme[lex_pos++] = current;
                (*pos)++;
                state = STATE_FRACTION;
            }
            else {                        // 数字结束
                token.type = TOKEN_INTEGER;
                token.lexeme[lex_pos] = '\0';
                return token;
            }
            break;

        case STATE_FRACTION:  // 识别小数部分
            if (isdigit(current)) {
                token.lexeme[lex_pos++] = current;
                (*pos)++;
            }
            else {                        // 小数结束
                // 检查至少有一个小数数字（如"123."是非法浮点数）
                if (isdigit(token.lexeme[lex_pos - 1])) {
                    token.type = TOKEN_FLOAT;
                }
                else {
                    token.type = TOKEN_ERROR;
                    strcpy_s(token.lexeme, 21, "无效浮点数");
                }
                token.lexeme[lex_pos] = '\0';
                return token;
            }
            break;
        case STATE_SLASH:  // 遇到斜杠后的状态判断
            if (current == '/') {         // 单行注释
                (*pos)++;
                state = STATE_SINGLE_COMMENT;
                lex_pos = 0; // 清空词素缓冲区（不保留注释内容）
            }
            else if (current == '*') { // 多行注释           
                (*pos)++;
                state = STATE_MULTI_COMMENT;
                lex_pos = 0;  //清空单词
            }
            else {                     // 普通除法运算符
                token.type = TOKEN_OPERATOR;
                token.lexeme[lex_pos] = '\0';
                return token;
            }
            break;

        case STATE_SINGLE_COMMENT: // 处理单行注释
            if (current == '\n' || current == '\0') { // 注释结束
                state = STATE_START; // 回到初始状态
                (*pos)++; // 跳过换行符
            }
            else {
                (*pos)++; // 继续跳过注释内容
            }
            break;
        case STATE_MULTI_COMMENT:
            if(current == '*') {
                (*pos)++;
                if (str[*pos] == '/') { // 注释结束
                    (*pos)++;
                    state = STATE_START;
                }
            }
            else if (current == '\0') { // 文件结束但注释未闭合
               // add_error(current_line, "未闭合的多行注释");
                token.type = TOKEN_ERROR;
                strcpy_s(token.lexeme, 32, "注释未闭合");
                return token;
            }
            else (*pos)++;
            break;
            
        }
    }
}

