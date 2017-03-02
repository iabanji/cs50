#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 0 || argc > 2)
    {
        printf("Unerror\n");
        return 1;
    }
    else if (argv[1] == NULL)
    {
        printf("Unerror\n");
        return 1;
    }
    else
    {
        int c = atoi(argv[1]);
        string name = GetString();
        if (name != NULL) 
        {
            if (c > 0)
            {
                int k = c % 26;
                for (int i = 0, n = strlen(name); i < n; i++)
                {
                    if (name[i] >= 'A' && name[i] <= 'Z')
                    {
                        int q = (int)name[i] + k;
                        if (q <= 90)
                        printf("%c", (char)q);
                        else 
                        {
                            int w = (q + 64) % 90;
                            printf("%c", (char)w);
                        }
                    }
                    else if (name[i] >= 'a' && name[i] <= 'z')
                    {
                        int q = (int)name[i] + k;
                        if (q <= 122)
                        printf("%c", (char)q);
                        else 
                        {
                            int w = (q + 96) % 122;
                            printf("%c", (char)w);
                        }
                    }
                    else printf("%c", name[i]);
                }
                printf("\n");
            }
        }
        return 0;
    }
}