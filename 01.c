#include <stdbool.h>
#include <stdio.h>

typedef struct line
{
    char data[8];
    struct line *next;
} line;

line lines[8] = {
    {.data = {0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01},
     .next = &lines[1]},
    {.data = {0x01, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01},
     .next = &lines[2]},
    {.data = {0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01},
     .next = &lines[3]},
    {.data = {0x01, 0x01, 0x00, 0x01, 0x05, 0x00, 0x00, 0x01},
     .next = &lines[4]},
    {.data = {0x03, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01},
     .next = &lines[5]},
    {.data = {0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
     .next = &lines[6]},
    {.data = {0x01, 0x01, 0x01, 0x04, 0x01, 0x01, 0x00, 0x00},
     .next = &lines[7]},
    {.data = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00},
     .next = NULL}};

int rdi[5] = {3, 5, 4, 2, -1}; // 添加末尾-1防止和迷宫中的0相等

int fun7(int *_rdi, int rsi, int edx, const char *input)
{
    int r8d = (rsi >= 0) ? rsi : rsi + 7;
    r8d /= 8;
    if (rsi < 0)
    {
        rsi += 3;
        rsi = (rsi % 8 + 8) % 8;
        rsi -= 3;
    }
    else
        rsi = (rsi % 8 + 8) % 8;

    if (rsi == 7 && r8d == 7)
        if (edx != 4)
            return 0;
        else if (edx == 4)
            return *input == '\0';

    int array1[4] = {0, 0, 1, -1};
    int array2[4] = {1, -1, 0, 0};
    int i = (int)((*input) % 4); // 0右1左2下3上
    r8d += array1[i];
    rsi += array2[i];

    line *r9 = lines;

    if (r8d > 7 || rsi > 7 || r8d < 0 || rsi < 0)
        return 0;

    if (r8d > 0)
    {
        int a = 0;
        do
        {
            r9 = r9->next;
            a++;
        } while (a != r8d);
    }

    if ((int)(r9->data[rsi]) == 1)
        return 0;

    if (_rdi[edx] == (int)(r9->data[rsi]))
    {
        return fun7(rdi, rsi + 8 * r8d, edx + 1, input + 1);
    }
    else if (_rdi[edx] != (int)(r9->data[rsi]))
    {
        return fun7(rdi, rsi + 8 * r8d, edx, input + 1);
    }
}

int main()
{
    char str[] = "002222110020003310221123003303310221220202";
    printf("%d", fun7(rdi, 0, 0, str));
}