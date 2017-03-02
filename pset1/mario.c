#include <cs50.h>
#include <stdio.h>


int main(void)
{
    int height;
    do
    {
        printf("Enter the height of piramid at 1 to 23: ");
        height = GetInt();
    }
    while(height < 1 || height > 23);
    
    int i = 0;
    while(i < height)
    {
        int m = 0;
        int t = height - i -1;
            while(m < t)
            {
                printf(" ");
                m++;
            }
        
        int n = 0;
        int r = i +2;
        while(n < r)
        {
            printf("#");
            n++;
        }
        printf("  \n");
        i++;
    }
}