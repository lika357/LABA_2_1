#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void clear_input(){
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        ;
    }
}

static char read_char(const char *prompt, const char *allowed){
    char c;
    int flag;

    printf("%s", prompt);
    while (1)
    {
        int scan_ok = (scanf("%c", &c) == 1);

        if (scan_ok == 0)
        {
            clear_input();
            printf("неверный ввод, допустимо:[%s]\n", allowed);
        }
        else
        {
            flag = 0;
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
                flag++;
            }

            if (strchr(allowed, c) != NULL && flag == 0)
            {
                return c; 
            }

            printf("неверный ввод, допустимо:[%s]\n", allowed);
        }
    }
}

static int read_int(const char *prompt, int min, int max){
    int val;

    printf("%s", prompt);
    while (1)
    {
        int scan_ok = (scanf("%d", &val) == 1);

        if (scan_ok == 0 || val < min || val > max)
        {
            printf("ошибка,введите целое число от %d до %d:", min, max);
            clear_input();
        }
        else
        {
            clear_input();
            return val; 
        }
    }
}


static float read_float(const char *prompt, float min, float max){
    float val;

    printf("%s", prompt);
    while (1)
    {
        int scan_ok = (scanf("%f", &val) == 1);

        if (scan_ok == 0 || val < min || val > max)
        {
            printf("ошибка, введите число от %.2f до %.2f:", min, max);
            clear_input();
        }
        else
        {
            clear_input();
            return val;
        }
    }
}

static matrix* create_matrix_interactive(const char *title, int max_val){
    matrix *m;
    type_info *type;
    char type_c;
    char fill_c;
    int size;

    printf("%s", title);
    size = read_int("размер матрицы (1-10):", 1, 10);
    type_c = read_char("тип элементов (i=int, c=complex):", "ic");

    if (type_c == 'i')
    {
        type = get_type_int();
    }
    else
    {
        type = get_complex_type();
    }

    m = matrix_create(size, type);
    if (m == NULL)
    {
        return NULL;
    }

    fill_c = read_char("заполнение (r=случайно, m=вручную): ", "rm");
    if (fill_c == 'r')
    {
        matrix_fill_random(m, max_val);
    }
    else
    {
        matrix_fill_manual(m, max_val);
    }

    if (read_char("изменить какой-либо элемент? (y=да, n==нет): ", "yn") == 'y')
    {
        int row;
        int col;
        void *elem;

        row = read_int("cтрока (1-10): ", 1, size) - 1;
        col = read_int("cтолбец (1-10): ", 1, size) - 1;
        elem = (char *)m->data + (row * m->size + col) * m->type->size;

        if (type_c == 'i')
        {
            int val;
            val = read_int("новое значение (int): ", -max_val, max_val);
            memcpy(elem, &val, sizeof(int));
        }
        else
        {
            complex val;
            val.real = read_float("действительная часть: ", -max_val, max_val);
            val.imag = read_float("мнимая часть: ", -max_val, max_val);
            memcpy(elem, &val, sizeof(complex));
        }
    }

    return m;
}

static void print_operation(const char *op, matrix *a, matrix *b, matrix *result){
    char *sa;
    char *sb;
    char *sr;

    sa = matrix_to_string(a);
    if (b != NULL)
    {
        sb = matrix_to_string(b);
    }
    else
    {
        sb = NULL;
    }
    sr = matrix_to_string(result);

    if (sa != NULL)
    {
        printf("%s", sa);
        free(sa);
    }

    printf("\n %s\n", op);

    if (sb != NULL)
    {
        printf("%s", sb);
        free(sb);
    }

    printf("\n  =\n");

    if (sr != NULL)
    {
        printf("%s", sr);
        free(sr);
    }
}

void io_run(){
    char mode;
    matrix *a;
    matrix *b;
    matrix *result;
    float scalar_f;
    complex scalar_c;

    mode = read_char(
        "алгоритм работы:\n"
        "  s - сложение\n"
        "  m - умножение матриц\n"
        "  f - умножение на float\n"
        "  c - умножение на complex\n"
        "Введите команду: ",
        "smfc"
    );

    a = NULL;
    b = NULL;
    result = NULL;
    scalar_f = 0.0f;
    scalar_c.real = 0.0f;
    scalar_c.imag = 0.0f;

    if (mode == 's' || mode == 'm')
    {
        a = create_matrix_interactive("матрица a ", 10);
        if (a != NULL)
        {
            b = create_matrix_interactive("матрица b", 10);
        }

        if (a != NULL && b != NULL)
        {
            if (a->type != b->type) {
             printf("ошибка ,матрицы разных типов (int и complex нельзя складывать или умножать)\n");
            }
            if (mode == 's')
            {
                result = matrix_summ(a, b);
                if (result == NULL) {
                    printf("ошибка,не удалось сложить матрицы\n");
            }
            else {
            print_operation("+", a, b, result);
            }
        }
            else
            {
                result = matrix_mul(a, b);
                if (result == NULL) {
                    printf("ошибка,не удалось сложить матрицы\n");
            }
            else {
            print_operation("*", a, b, result);
            }
            }
        }
    }
    else if (mode == 'f')
    {
        a = create_matrix_interactive("матрица", 10);
        if (a != NULL)
        {
            scalar_f = read_float("введите скаляр (float): ", -100.0f, 100.0f);
            result = matrix_mul_scalar(a, scalar_f);
            print_operation("float", a, NULL, result);
        }
    }
    else if (mode == 'c')
    {
        a = create_matrix_interactive("матрица", 10);
        if (a != NULL)
        {
            if (a->type == get_type_int()) {
            printf("ошибка: умножение на комплексный скаляр возможно только для комплексных матриц\n");
            }
            else{
            scalar_c.real = read_float("действительная часть скаляра: ", -100.0f, 100.0f);
            scalar_c.imag = read_float("мнимая часть скаляра: ", -100.0f, 100.0f);
            result = matrix_mul_scalar_complex(a, &scalar_c);
            print_operation("complex", a, NULL, result);
            }
    }

    matrix_free(a);
    matrix_free(b);
    matrix_free(result);
    printf("\nпрограмма завершена\n");
}
}

