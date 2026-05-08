#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUMBER 200

typedef struct {
    char bracket;  // '(' or '{'
    int line;
} StackItem;

int main() {
    FILE *file_c = fopen("./example.c", "r");
    if (!file_c) {
        puts("error");
        return 0;
    }

    StackItem stack[MAX_NUMBER];
    int top = 0;
    char line[MAX_NUMBER];
    int line_no = 0;
    char output[MAX_NUMBER];
    int output_index = 0;

    int in_comment = 0;
    int in_char = 0;
    int in_string = 0;

    while (fgets(line, sizeof(line), file_c)) {
        line_no++;
        line[strcspn(line, "\n")] = '\0';  // 去掉换行符
        int len = strlen(line);

        for (int i = 0; i < len; i++) {

            // 处理注释
            if (!in_char && !in_string) {
                if (!in_comment && i + 1 < len && line[i] == '/' && line[i + 1] == '/') break; // 单行注释
                if (!in_comment && i + 1 < len && line[i] == '/' && line[i + 1] == '*') { in_comment = 1; i++; continue; }
                if (in_comment && i + 1 < len && line[i] == '*' && line[i + 1] == '/') { in_comment = 0; i++; continue; }
            }
            if (in_comment) continue;

            // 处理字符常量
            if (line[i] == '\'' && !in_string) { in_char = !in_char; continue; }

            // 处理字符串
            if (line[i] == '\"' && !in_char) { in_string = !in_string; continue; }

            // 处理括号
            if (!in_char && !in_string) {
                if (line[i] == '(' || line[i] == '{') {
                    stack[top].bracket = line[i];
                    stack[top].line = line_no;
                    top++;
                    output[output_index++] = line[i]; // 左括号入栈即输出
                } else if (line[i] == ')') {
                    if (top == 0) {
                        printf("without maching ')' at line %d", line_no);
                        fclose(file_c);
                        return 0;
                    }
                    if (stack[top - 1].bracket != '(') {
                        // 栈顶不是 '('，输出栈顶行号
                        printf("without maching ')' at line %d", line_no);
                        fclose(file_c);
                        return 0;
                    }
                    top--;
                    output[output_index++] = ')';  // 匹配成功才输出
                } else if (line[i] == '}') {
                    if (top == 0) {
                        printf("without maching '}' at line %d", line_no);
                        fclose(file_c);
                        return 0;
                    }
                    if (stack[top - 1].bracket != '{') {
                        // 栈顶不是 '{'，输出栈顶行号
                        if (stack[top - 1].bracket == '(')
                            printf("without maching '(' at line %d", stack[top - 1].line);
                        else
                            printf("without maching '{' at line %d", stack[top - 1].line);
                        fclose(file_c);
                        return 0;
                    }
                    top--;
                    output[output_index++] = '}';  // 匹配成功才输出
                }
            }
        }
    }

    // 栈中剩余未匹配的左括号
    if (top > 0) {
        if (stack[top - 1].bracket == '(') {
            printf("without maching '(' at line %d", stack[top - 1].line);
        } else {
            printf("without maching '{' at line %d", stack[top - 1].line);
        }
        fclose(file_c);
        return 0;
    }

    // 输出匹配成功的括号序列
    output[output_index] = '\0';
    printf("%s\n", output);

    fclose(file_c);
    return 0;
}