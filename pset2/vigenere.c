#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string key = argv[1];
    if (argc == 0 || argc > 2)
    {
        printf("Unerror\n");
        return 1;
    }
    else if (key == NULL)
    {
        printf("Unerror\n");
        return 1;
    }
    else if (key != NULL)
    {
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            if (!isalpha(key[i]))
            {
                printf("Unerror\n");
                return 1;
            }
        }
        string name = GetString();
        if (name != NULL) 
        {
            int count_key = strlen(key);
            int count_name = 0;
            int e = 0;
            char c_n[count_name];
            for (int i = 0, n = strlen(name); i < n; i++)
            {
                if (isalpha(name[i]))
                {
                    c_n[e] = name[i];
                    count_name++;
                    e++;
                }
            }
            int j = 0;
            for (int i = 0, n = strlen(name); i < n; i++)
            {
                int t = j % count_key;
                char c = toupper(key[t]);
                int k = (int)c % 65;
                if (name[i] >= 'A' && name[i] <= 'Z')
                {
                    int q = (int)name[i] + k;
                    if (q <= 90)
                    {
                        j++;
                        printf("%c", (char)q);
                    }
                    else 
                    {
                        int w = (q + 64) % 90;
                        j++;
                        printf("%c", (char)w);
                    }
                }
                else if (name[i] >= 'a' && name[i] <= 'z')
                {
                    int q = (int)name[i] + k;
                    if (q <= 122)
                    {
                        j++;
                        printf("%c", (char)q);
                    }
                    else 
                    {
                        int w = (q + 96) % 122;
                        j++;
                        printf("%c", (char)w);
                    }
                }
                else printf("%c", name[i]);
            }
            printf("\n");
        }
        else
        {
            printf("Unerror\n");
            return 1;    
        }
    }
    return 0;
}