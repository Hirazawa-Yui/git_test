#include <stdio.h>
int func4(int edi, int esi, int edx)
{
    int ebx = (edx - esi) / 2 + esi;

    if (ebx > edi)
    {
        return func4(edi, esi, ebx - 1) + ebx;
    }
    else if (ebx < edi)
    {
        return func4(edi, ebx + 1, edx) + ebx;
    }
    else
    {
        return ebx;
    }
}

int main()
{
    static char char_table[3][13] = {{'d', 'o', 32, 'y', 'o', 'u', 32, 'w', 'a', 'n', 't', 32, 'a'}, {32, 109, 105, 100, 116, 101, 114, 109, 32, 101, 120, 97, 109}, {0}};
    static char ans[] = "abcdefghijklmnopqrstuvwxyyz";
    printf("%s?\n", char_table);
    printf("%c%c%c!\n",
           (char)(((char **)ans)[6]),
           (char)(((char *)ans)[4]),
           (char)(ans[18]));
    return 0;
}