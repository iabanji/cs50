#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    printf("Введите ФИО: ");
    string name = GetString();
    if (name != NULL) 
    {
        printf("Инициалы: ");
        if ((name[0] >= 'A' && name[0] <= 'Z') || (name[0] >= 'a' && name[0] <= 'z'))
        printf("%c", toupper(name[0]));
        int k = strlen(name);
        for (int i = 0; i < k; i++)
        {
            char y = name[i];
            char x = name[i+1];
            if (((int)y == 32) && ((((int)x >= 65) && ((int)x <= 90)) || (((int)x >= 97) && ((int)x <= 122))))
            {
                printf("%c", toupper((char) x));
            }
        }
        printf("\n");
    }
}