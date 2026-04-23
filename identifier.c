#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define Max     300
#define Max_word 64
#define Max_num  200

char sentence[Max];
char words[Max_num][Max_word];
int  word_count = 0;

const char *keywords[] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if","inline",
    "int","long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while"
};
#define KW_COUNT ((int)(sizeof(keywords)/sizeof(keywords[0])))

int is_keyword(const char *w) {
    for (int i = 0; i < KW_COUNT; i++)
        if (strcmp(keywords[i], w) == 0) return 1;
    return 0;
}

int is_duplicate(const char *w) {
    for (int i = 0; i < word_count; i++)
        if (strcmp(words[i], w) == 0) return 1;
    return 0;
}

int cmp(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main(void) {
    fgets(sentence, Max, stdin);
    int len = strlen(sentence);
    if (len > 0 && sentence[len-1] == '\n') sentence[--len] = '\0';

    int i = 0;
    while (i < len) {
        /* 标识符：以字母或下划线开头 */
        if (isalpha((unsigned char)sentence[i]) || sentence[i] == '_') {
            char word[Max_word];
            int  wlen = 0;
            while (i < len && (isalnum((unsigned char)sentence[i]) || sentence[i] == '_')) {
                if (wlen < Max_word - 1) word[wlen++] = sentence[i];
                i++;
            }
            word[wlen] = '\0';
            /* 跳过关键字和重复词 */
            if (!is_keyword(word) && !is_duplicate(word) && word_count < Max_num)
                strcpy(words[word_count++], word);
            continue;
        }
        /* 跳过数字字面量 */
        if (isdigit((unsigned char)sentence[i])) {
            while (i < len && (isalnum((unsigned char)sentence[i]) || sentence[i] == '.')) i++;
            continue;
        }
        i++;
    }

    qsort(words, word_count, Max_word, cmp);
    for (int j = 0; j < word_count; j++)
        printf("%s ", words[j]);
    return 0;
}
