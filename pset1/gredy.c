#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void) 
{
    float y;
    do
    {
        printf("Please enter how much of coins i can get you: ");
        y = GetFloat(); 
    }
    while(y < 0);
    
    int x = round(y*100);
    
    int tw = x % 25;
    int n_1 = (x - tw)/25;
    int tn = tw % 10;
    int n_2 = (tw - tn)/10;
    int fv = tn % 5;
    int n_3 = (tn - fv)/5;
    
    int num = n_1 + n_2 + n_3 + fv;
    printf("Take %i coins!\n", num);
    
}
