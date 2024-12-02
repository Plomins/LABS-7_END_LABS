#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

#define MAX_LEN 256

int my_strlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void my_strcpy(char* dest, const char* src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

int my_strncmp(const char* str1, const char* str2, int n) {
    for (int i = 0; i < n; i++) {
        if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
            return str1[i] - str2[i];
        }
    }
    return 0;
}

void trim_newline(char* str) {
    int len = my_strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void reverse_word(char* str, int k) {
    int word_count = 0, i = 0, j = 0, start = 0, end = 0;

    while (str[i] != '\0') {
        if (str[i] == ' ' || str[i + 1] == '\0') {
            word_count++;
            if (word_count == k) {
                start = j;
                end = (str[i + 1] == '\0') ? i : i - 1;

                while (start < end) {
                    char temp = str[start];
                    str[start] = str[end];
                    str[end] = temp;
                    start++;
                    end--;
                }
                return;
            }
            j = i + 1;
        }
        i++;
    }

    printf("Слово номер %d не найдено в строке.\n", k);
}

void insert_before_substring(char* str, const char* substr, const char* s0) {
    char result[MAX_LEN * 2]; // Увеличенный размер результата для учета вставок
    int i = 0, j = 0, k = 0, s0_len = my_strlen(s0);
    int substr_len = my_strlen(substr);

    while (str[i] != '\0') {
        if (my_strncmp(&str[i], substr, substr_len) == 0) {
            if (i != 0 && str[i - 1] != ' ') {
                result[j++] = ' '; // Добавляем пробел перед вставкой, если требуется
            }
            for (k = 0; k < s0_len; k++) {
                result[j++] = s0[k];
            }
        }
        result[j++] = str[i++];
    }
    result[j] = '\0';
    my_strcpy(str, result);
}

int min_word_length(const char* str) {
    int min_len = MAX_LEN, current_len = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            if (current_len < min_len && current_len > 0) {
                min_len = current_len;
            }
            current_len = 0;
        }
        else {
            current_len++;
        }
    }

    if (current_len < min_len && current_len > 0) {
        min_len = current_len;
    }
    return min_len;
}

void insertion_sort(char** arr, int n) {
    int i, j;
    char* key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && (min_word_length(arr[j]) > min_word_length(key) ||
            (min_word_length(arr[j]) == min_word_length(key) && my_strlen(arr[j]) > my_strlen(key)))) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int get_int_input(const char* prompt) {
    int value;
    char buffer[MAX_LEN];

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, MAX_LEN, stdin) != NULL && sscanf(buffer, "%d", &value) == 1) {
            return value;
        }
        printf("Некорректный ввод. Пожалуйста, введите целое число.\n");
    }
}

void execute_task() {
    while (1) {
        int choice = get_int_input("Выберите задачу:\n1. Перевернуть k-ое слово в строке\n2. Вставить строку S0 перед подстрокой C в строке S\n3. Сортировка массива строк методом вставок по длине самого короткого слова\n4. Выход\nВаш выбор: ");

        if (choice == 1) {
            char str[MAX_LEN];
            int k;

            printf("Введите строку: ");
            getchar();
            fgets(str, MAX_LEN, stdin);
            trim_newline(str);

            k = get_int_input("Введите номер слова для переворота: ");
            reverse_word(str, k);

            printf("Измененная строка: %s\n", str);

        }
        else if (choice == 2) {
            char str[MAX_LEN], s0[MAX_LEN], substr[MAX_LEN];

            printf("Введите строку S: ");
            getchar();
            fgets(str, MAX_LEN, stdin);
            trim_newline(str);

            printf("Введите подстроку C: ");
            fgets(substr, MAX_LEN, stdin);
            trim_newline(substr);

            printf("Введите строку S0: ");
            fgets(s0, MAX_LEN, stdin);
            trim_newline(s0);

            insert_before_substring(str, substr, s0);
            printf("Измененная строка: %s\n", str);

        }
        else if (choice == 3) {
            int n = get_int_input("Введите количество строк: ");

            char** arr = (char**)malloc(n * sizeof(char*));
            for (int i = 0; i < n; i++) {
                arr[i] = (char*)malloc(MAX_LEN * sizeof(char));
            }

            printf("Введите строки:\n");
            getchar();
            for (int i = 0; i < n; i++) {
                fgets(arr[i], MAX_LEN, stdin);
                trim_newline(arr[i]);
            }

            insertion_sort(arr, n);

            printf("Отсортированный массив строк:\n");
            for (int i = 0; i < n; i++) {
                printf("%s\n", arr[i]);
                free(arr[i]);
            }
            free(arr);

        }
        else if (choice == 4) {
            printf("Выход из программы.\n");
            break;
        }
        else {
            printf("Некорректный выбор. Попробуйте снова.\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    execute_task();
    return 0;
}
